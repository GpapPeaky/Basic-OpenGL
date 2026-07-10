#pragma once

#include "OGL_Object.hpp"

#include <string>
#include <vector>

typedef struct OGL_ONode{
    std::string id;                     /* Identifier */
    OGL_Object* o;                      /* Object data */
    int active = 1;                     /* Node is active, if NOT active, it will not be rendered, and cannot be interacted with! If the node has children
                                            they will also be omitted from updates and render visits */
    int visible = 1;                    /* If visible is 0, then the object will update but it will NOT be rendered */
    std::vector<OGL_ONode*> children;   /* Object's children */
}OGL_ONode;

/**
 * @brief Get the N-th child of a node
 *
 * @param root Object node
 * @param N N-th child
 *
 * @returns The N-th child of the specified node object,
 * if found, else nullptr
 */
OGL_ONode* OGL_GetNthChild(OGL_ONode* root, unsigned int N);

/**
 * @brief Get the child of a node with the matching identifier
 *
 * @param root Object node
 * @param id Identifer
 *
 * @returns The child node with that specific id,
 * else nullptr
 */
OGL_ONode* OGL_GetChild(OGL_ONode* root, std::string id);

/**
 * @brief Attach a node to a specific parent,
 * effectively push a node object into the parent node's
 * children vector
 *
 * @param parent Parent node to attach to
 * @param child Child node to attach to
 */
void OGL_AttachChild(OGL_ONode* parent, OGL_ONode* child);

/**
 * @brief Allocate memory for a new node
 *
 * @param o Object data
 * @param id Node identifier
 * 
 * @returns The created node object
 */
OGL_ONode* OGL_CreateNode(OGL_Object* o, std::string id);

/* Current rendering scene, this is the root of our program */
extern OGL_ONode* OGL_Scene;

