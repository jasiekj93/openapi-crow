#include "OpenapiJson.hpp"

#include "Post.hpp"
#include "Get.hpp"

using namespace openapi::route;

OpenapiJson::OpenapiJson(Server& server)
    : Base("/openapi.json")
    , server(server)
{
}

crow::response OpenapiJson::operator()(const crow::request&) const
{
    crow::response response(200);
    response.set_header("Content-Type", "application/json");
    response.set_header("Access-Control-Allow-Origin", "*");
    response.body = getSpecification();
    return response;
}

std::string OpenapiJson::getSpecification() const
{
    crow::json::wvalue specification;
    
    // OpenAPI 3.0 specification
    specification["openapi"] = "3.0.3";
    
    addInfo(specification);
    addServers(specification);
    addPaths(specification);
    
    return specification.dump(); 
}

void OpenapiJson::addInfo(crow::json::wvalue& specification) const
{
    auto info = server.getInfo();
    
    specification["info"]["title"] = info.title;
    specification["info"]["version"] = info.version;

    if(info.description.has_value())
        specification["info"]["description"] = info.description.value();

    if(info.contact.has_value())
    {
        specification["info"]["contact"]["name"] = info.contact->name;

        if(info.contact->url.has_value())
            specification["info"]["contact"]["url"] = info.contact->url.value();

        if(info.contact->email.has_value())
            specification["info"]["contact"]["email"] = info.contact->email.value();
    }
}

void OpenapiJson::addServers(crow::json::wvalue& specification) const
{
    specification["servers"] = crow::json::wvalue::list();
    crow::json::wvalue json;

    auto serverUrl = "http://" + server.getHost() + ":" + std::to_string(server.getPort());
    json["url"] = serverUrl;

    if(server.getDescription().has_value())
        json["description"] = server.getDescription().value();

    specification["servers"][0] = std::move(json);
}

void OpenapiJson::addPaths(crow::json::wvalue& specification) const
{
    specification["paths"] = crow::json::wvalue::object();
    specification["components"]["schemas"] = crow::json::wvalue::object();

    for(const auto& route : server.getRoutes())
    {
        auto path = route->getPath();
        if(path == "/openapi.json" or
           path == "/docs" or
           path == "/api-docs")
            continue; 

        crow::json::wvalue pathItem;
        if(route->getMethod() == crow::HTTPMethod::GET)
            addGetPath(pathItem, specification, route);
        else if(route->getMethod() == crow::HTTPMethod::POST)
            addPostPath(pathItem, specification, route);

        specification["paths"][path] = std::move(pathItem);
    }
}

void OpenapiJson::addGetPath(crow::json::wvalue& pathItem, 
    crow::json::wvalue& specification, 
    const std::shared_ptr<Base>& route) const
{
    auto getRoute = dynamic_cast<Get*>(route.get());

    if(getRoute)
    {
        auto operation = getRoute->getSpecification();
        pathItem["get"]["summary"] = operation.summary;
        pathItem["get"]["description"] = operation.description;
        
        if(operation.responses.has_value())
        {
            for(const auto& [code, description, contentSchema] : operation.responses.value())
            {
                pathItem["get"]["responses"][std::to_string(code)]["description"] = description;
                
                if(contentSchema.has_value())
                {
                    pathItem["get"]["responses"][std::to_string(code)]["content"]["application/json"]["schema"]["$ref"] = "#/components/schemas/" + contentSchema.value();
                    specification["components"]["schemas"][contentSchema.value()] = getRoute->getSchema(contentSchema.value());
                }
            }
        }
    }
}

void OpenapiJson::addPostPath(crow::json::wvalue& pathItem, 
    crow::json::wvalue& specification, 
    const std::shared_ptr<Base>& route) const
{
    auto postRoute = dynamic_cast<Post*>(route.get());

    if(postRoute)
    {
        auto operation = postRoute->getSpecification();
        pathItem["post"]["summary"] = operation.summary;
        pathItem["post"]["description"] = operation.description;
        
        if(operation.requestBody.has_value())
        {
            auto& requestBody = operation.requestBody.value();
            pathItem["post"]["requestBody"]["required"] = requestBody.isRequired;
            
            if(requestBody.contentSchema.has_value())
            {
                auto schemaName = requestBody.contentSchema.value();
                pathItem["post"]["requestBody"]["content"]["application/json"]["schema"]["$ref"] = "#/components/schemas/" + schemaName;
                specification["components"]["schemas"][schemaName] = postRoute->getSchema(schemaName);
            }
        }

        if(operation.responses.has_value())
        {
            for(const auto& [code, description, contentSchema] : operation.responses.value())
            {
                pathItem["post"]["responses"][std::to_string(code)]["description"] = description;
                
                if(contentSchema.has_value())
                {
                    pathItem["post"]["responses"][std::to_string(code)]["content"]["application/json"]["schema"]["$ref"] = "#/components/schemas/" + contentSchema.value();
                    specification["components"]["schemas"][contentSchema.value()] = postRoute->getSchema(contentSchema.value());
                }
            }
        }
    }
}