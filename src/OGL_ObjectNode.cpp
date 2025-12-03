#include "OGL_ObjectNode.hpp"

OGL_ONode* OGL_GetNthChild(OGL_ONode* root, unsigned int N){
    if(!root) return nullptr;

    if (N >= root->children.size()) return nullptr;

    OGL_ONode* c = root->children.at(N);
    
    if(c != nullptr){
        return c;
    }
    
    return nullptr;
}

OGL_ONode* OGL_GetChild(OGL_ONode* root, std::string id){
    if(!root) return nullptr;

    for(auto s : root->children){
        if(s->id == id){
            return s;
        }
    }
    
    return nullptr;
}

void OGL_AttachChild(OGL_ONode* parent, OGL_ONode* child){
    if(!parent){
        std::fprintf(stderr, "OGL_ERR: Null parent node to attach child %s\n", child->id);

        return;
    }

    /* First check if a child node with the same id exists */
    if(OGL_GetChild(parent, child->id) != nullptr){
        std::fprintf(stderr, "OGL_ERR: Child node %s exists for parent %s, change one of the identifiers\n", child->id.c_str(), parent->id.c_str());
        
        return;
    }
    
    /* Secure attachment */
    parent->children.push_back(child);
    
    return;
}

OGL_ONode* OGL_CreateNode(OGL_Object* o, std::string id){
    OGL_ONode* onode = new OGL_ONode;
    
    onode->o = o;
    onode->id = id;
    
    return onode;
}

OGL_ONode* OGL_Scene;
