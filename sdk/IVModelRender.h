#pragma once

#include "../utilities/utilities.h"
#include "../math/vector3d.h"
#include "../math/qangle.h"

// https://github.com/ValveSoftware/source-sdk-2013/blob/master/mp/src/public/engine/ivmodelrender.h

class IClientRenderable;
class IMaterial;

// ik this is really meant to be here but boo fucking hoo
struct RenderableInfo_t {
    IClientRenderable* renderable;
    void* alpha_property;
    int enum_count;
    int render_frame;
    unsigned short first_shadow;
    unsigned short leaf_list;
    short area;
    std::uint16_t flags;
    std::uint16_t flags2;
    vector3d_t bloated_abs_mins;
    vector3d_t bloated_abs_maxs;
    vector3d_t abs_mins;
    vector3d_t abs_maxs;
    int pad;
};

// and ik this is really meant to be here but boo fucking hoo
enum OverrideType_t {
    OVERRIDE_NORMAL = 0,
    OVERRIDE_BUILD_SHADOWS,
    OVERRIDE_DEPTH_WRITE,
    OVERRIDE_SSAO_DEPTH_WRITE,
};

// holy shit this is meant to be here
struct ModelRenderInfo_t {
    vector3d_t origin;
    qangle_t angles;
    char _pad0[ 0x4 ];
    IClientRenderable* renderable;
    const void* model;
    const void* model_to_world;
    const void* lighting_offset;
    const vector3d_t* lighting_origin;
    int flags;
    int entity_index;
    int skin;
    int body;
    int hitboxset;
    unsigned short instance;
};

class IVModelRender {
public:
    // this causes a material to be used when rendering the model instead 
    // of the materials the model was compiled with
    virtual_fn( forced_material_override( IMaterial* new_material, OverrideType_t override_type = OVERRIDE_NORMAL, int overrides = 0 ), 1, void( __thiscall* )( void*, IMaterial*, OverrideType_t, int ), new_material, override_type, overrides );
};