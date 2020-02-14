/**
 * @file lv_style.h
 *
 */

#ifndef LV_STYLE_H
#define LV_STYLE_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#include <stdbool.h>
#include "../lv_font/lv_font.h"
#include "../lv_misc/lv_color.h"
#include "../lv_misc/lv_area.h"
#include "../lv_misc/lv_anim.h"
#include "../lv_misc/lv_types.h"
#include "../lv_draw/lv_draw_blend.h"

/*********************
 *      DEFINES
 *********************/
#define LV_RADIUS_CIRCLE (LV_COORD_MAX) /**< A very big radius to always draw as circle*/
LV_EXPORT_CONST_INT(LV_RADIUS_CIRCLE);

#define LV_DEBUG_STYLE_SENTINEL_VALUE       0x2288AAEE
#define LV_DEBUG_STYLE_LIST_SENTINEL_VALUE  0x9977CCBB

/**********************
 *      TYPEDEFS
 **********************/

/*Border types (Use 'OR'ed values)*/
enum {
    LV_BORDER_SIDE_NONE     = 0x00,
    LV_BORDER_SIDE_BOTTOM   = 0x01,
    LV_BORDER_SIDE_TOP      = 0x02,
    LV_BORDER_SIDE_LEFT     = 0x04,
    LV_BORDER_SIDE_RIGHT    = 0x08,
    LV_BORDER_SIDE_FULL     = 0x0F,
    LV_BORDER_SIDE_INTERNAL = 0x10, /**< FOR matrix-like objects (e.g. Button matrix)*/
};
typedef uint8_t lv_border_side_t;

enum {
    LV_GRAD_DIR_NONE,
    LV_GRAD_DIR_VER,
    LV_GRAD_DIR_HOR,
};

typedef uint8_t lv_grad_dir_t;

#define LV_STYLE_PROP_INIT(name, group, id, attr)  name = (((group << 4) + id) | ((attr) << 8))

#define LV_STYLE_ID_MASK 0x00FF

#define LV_STYLE_ATTR_NONE          0
#define LV_STYLE_ATTR_INHERIT       (1 << 7)

#define _LV_STYLE_CLOSEING_PROP     0xFF

typedef union {
    struct {
        uint8_t state       :7; /* To which state the property refers to*/
        uint8_t inherit     :1; /*1: The property can be inherited*/
    }bits;
    uint8_t full;
}lv_style_attr_t;


#define LV_STYLE_ID_VALUE 0x0   /*max 6 pcs*/
#define LV_STYLE_ID_COLOR 0x6   /*max 4 pcs*/
#define LV_STYLE_ID_OPA   0xA   /*max 4 pcs*/
#define LV_STYLE_ID_PTR   0xE   /*max 2 pcs*/

enum {
    LV_STYLE_PROP_INIT(LV_STYLE_RADIUS,             0x0, LV_STYLE_ID_VALUE + 0, LV_STYLE_ATTR_NONE),
    LV_STYLE_PROP_INIT(LV_STYLE_CLIP_CORNER,        0x0, LV_STYLE_ID_VALUE + 1, LV_STYLE_ATTR_NONE),
    LV_STYLE_PROP_INIT(LV_STYLE_TRANSITION_TIME,    0x0, LV_STYLE_ID_VALUE + 2, LV_STYLE_ATTR_NONE),
    LV_STYLE_PROP_INIT(LV_STYLE_SIZE,               0x0, LV_STYLE_ID_VALUE + 3, LV_STYLE_ATTR_NONE),
    LV_STYLE_PROP_INIT(LV_STYLE_OPA_SCALE,          0x0, LV_STYLE_ID_OPA + 0,   LV_STYLE_ATTR_INHERIT),

    LV_STYLE_PROP_INIT(LV_STYLE_PAD_TOP,            0x1, LV_STYLE_ID_VALUE + 0, LV_STYLE_ATTR_NONE),
    LV_STYLE_PROP_INIT(LV_STYLE_PAD_BOTTOM,         0x1, LV_STYLE_ID_VALUE + 1, LV_STYLE_ATTR_NONE),
    LV_STYLE_PROP_INIT(LV_STYLE_PAD_LEFT,           0x1, LV_STYLE_ID_VALUE + 2, LV_STYLE_ATTR_NONE),
    LV_STYLE_PROP_INIT(LV_STYLE_PAD_RIGHT,          0x1, LV_STYLE_ID_VALUE + 3, LV_STYLE_ATTR_NONE),
    LV_STYLE_PROP_INIT(LV_STYLE_PAD_INNER,          0x1, LV_STYLE_ID_VALUE + 4, LV_STYLE_ATTR_NONE),

    LV_STYLE_PROP_INIT(LV_STYLE_BG_BLEND_MODE,      0x2, LV_STYLE_ID_VALUE + 0, LV_STYLE_ATTR_NONE),
    LV_STYLE_PROP_INIT(LV_STYLE_BG_MAIN_STOP,      0x2, LV_STYLE_ID_VALUE + 1, LV_STYLE_ATTR_NONE),
    LV_STYLE_PROP_INIT(LV_STYLE_BG_GRAD_STOP,       0x2, LV_STYLE_ID_VALUE + 2, LV_STYLE_ATTR_NONE),
    LV_STYLE_PROP_INIT(LV_STYLE_BG_GRAD_DIR,        0x2, LV_STYLE_ID_VALUE + 3, LV_STYLE_ATTR_NONE),
    LV_STYLE_PROP_INIT(LV_STYLE_BG_COLOR,           0x2, LV_STYLE_ID_COLOR + 0, LV_STYLE_ATTR_NONE),
    LV_STYLE_PROP_INIT(LV_STYLE_BG_GRAD_COLOR,      0x2, LV_STYLE_ID_COLOR + 1, LV_STYLE_ATTR_NONE),
    LV_STYLE_PROP_INIT(LV_STYLE_BG_OPA,             0x2, LV_STYLE_ID_OPA   + 0, LV_STYLE_ATTR_NONE),

    LV_STYLE_PROP_INIT(LV_STYLE_BORDER_WIDTH,       0x3, LV_STYLE_ID_VALUE + 0, LV_STYLE_ATTR_NONE),
    LV_STYLE_PROP_INIT(LV_STYLE_BORDER_SIDE,        0x3, LV_STYLE_ID_VALUE + 1, LV_STYLE_ATTR_NONE),
    LV_STYLE_PROP_INIT(LV_STYLE_BORDER_BLEND_MODE,  0x3, LV_STYLE_ID_VALUE + 2, LV_STYLE_ATTR_NONE),
    LV_STYLE_PROP_INIT(LV_STYLE_BORDER_POST,        0x3, LV_STYLE_ID_VALUE + 3, LV_STYLE_ATTR_NONE),
    LV_STYLE_PROP_INIT(LV_STYLE_BORDER_COLOR,       0x3, LV_STYLE_ID_COLOR + 0, LV_STYLE_ATTR_NONE),
    LV_STYLE_PROP_INIT(LV_STYLE_BORDER_OPA,         0x3, LV_STYLE_ID_OPA   + 0, LV_STYLE_ATTR_NONE),

    LV_STYLE_PROP_INIT(LV_STYLE_OUTLINE_WIDTH,       0x4, LV_STYLE_ID_VALUE + 0, LV_STYLE_ATTR_NONE),
    LV_STYLE_PROP_INIT(LV_STYLE_OUTLINE_PAD,         0x4, LV_STYLE_ID_VALUE + 1, LV_STYLE_ATTR_NONE),
    LV_STYLE_PROP_INIT(LV_STYLE_OUTLINE_BLEND_MODE,  0x4, LV_STYLE_ID_VALUE + 2, LV_STYLE_ATTR_NONE),
    LV_STYLE_PROP_INIT(LV_STYLE_OUTLINE_COLOR,       0x4, LV_STYLE_ID_COLOR + 0, LV_STYLE_ATTR_NONE),
    LV_STYLE_PROP_INIT(LV_STYLE_OUTLINE_OPA,         0x4, LV_STYLE_ID_OPA   + 0, LV_STYLE_ATTR_NONE),

    LV_STYLE_PROP_INIT(LV_STYLE_SHADOW_WIDTH,       0x5, LV_STYLE_ID_VALUE + 0, LV_STYLE_ATTR_NONE),
    LV_STYLE_PROP_INIT(LV_STYLE_SHADOW_OFFSET_X,    0x5, LV_STYLE_ID_VALUE + 1, LV_STYLE_ATTR_NONE),
    LV_STYLE_PROP_INIT(LV_STYLE_SHADOW_OFFSET_Y,    0x5, LV_STYLE_ID_VALUE + 2, LV_STYLE_ATTR_NONE),
    LV_STYLE_PROP_INIT(LV_STYLE_SHADOW_SPREAD,      0x5, LV_STYLE_ID_VALUE + 3, LV_STYLE_ATTR_NONE),
    LV_STYLE_PROP_INIT(LV_STYLE_SHADOW_BLEND_MODE,  0x5, LV_STYLE_ID_VALUE + 4, LV_STYLE_ATTR_NONE),
    LV_STYLE_PROP_INIT(LV_STYLE_SHADOW_COLOR,       0x5, LV_STYLE_ID_COLOR + 0, LV_STYLE_ATTR_NONE),
    LV_STYLE_PROP_INIT(LV_STYLE_SHADOW_OPA,         0x5, LV_STYLE_ID_OPA   + 0, LV_STYLE_ATTR_NONE),

    LV_STYLE_PROP_INIT(LV_STYLE_PATTERN_BLEND_MODE,    0x6, LV_STYLE_ID_VALUE + 0, LV_STYLE_ATTR_NONE),
    LV_STYLE_PROP_INIT(LV_STYLE_PATTERN_REPEAT,        0x6, LV_STYLE_ID_VALUE + 1, LV_STYLE_ATTR_NONE),
    LV_STYLE_PROP_INIT(LV_STYLE_PATTERN_RECOLOR,       0x6, LV_STYLE_ID_COLOR + 0, LV_STYLE_ATTR_NONE),
    LV_STYLE_PROP_INIT(LV_STYLE_PATTERN_OPA,           0x6, LV_STYLE_ID_OPA   + 0, LV_STYLE_ATTR_NONE),
    LV_STYLE_PROP_INIT(LV_STYLE_PATTERN_RECOLOR_OPA,   0x6, LV_STYLE_ID_OPA   + 1, LV_STYLE_ATTR_NONE),
    LV_STYLE_PROP_INIT(LV_STYLE_PATTERN_IMAGE,         0x6, LV_STYLE_ID_PTR   + 0, LV_STYLE_ATTR_NONE),

    LV_STYLE_PROP_INIT(LV_STYLE_VALUE_LETTER_SPACE,  0x7, LV_STYLE_ID_VALUE + 0, LV_STYLE_ATTR_NONE),
    LV_STYLE_PROP_INIT(LV_STYLE_VALUE_LINE_SPACE,    0x7, LV_STYLE_ID_VALUE + 1, LV_STYLE_ATTR_NONE),
    LV_STYLE_PROP_INIT(LV_STYLE_VALUE_BLEND_MODE,    0x7, LV_STYLE_ID_VALUE + 2, LV_STYLE_ATTR_NONE),
    LV_STYLE_PROP_INIT(LV_STYLE_VALUE_OFS_X,         0x7, LV_STYLE_ID_VALUE + 3, LV_STYLE_ATTR_NONE),
    LV_STYLE_PROP_INIT(LV_STYLE_VALUE_OFS_Y,         0x7, LV_STYLE_ID_VALUE + 4, LV_STYLE_ATTR_NONE),
    LV_STYLE_PROP_INIT(LV_STYLE_VALUE_ALIGN,         0x7, LV_STYLE_ID_VALUE + 5, LV_STYLE_ATTR_NONE),
    LV_STYLE_PROP_INIT(LV_STYLE_VALUE_COLOR,         0x7, LV_STYLE_ID_COLOR + 0, LV_STYLE_ATTR_NONE),
    LV_STYLE_PROP_INIT(LV_STYLE_VALUE_OPA,           0x7, LV_STYLE_ID_OPA   + 0, LV_STYLE_ATTR_NONE),
    LV_STYLE_PROP_INIT(LV_STYLE_VALUE_FONT,          0x7, LV_STYLE_ID_PTR   + 0, LV_STYLE_ATTR_NONE),
    LV_STYLE_PROP_INIT(LV_STYLE_VALUE_STR,           0x7, LV_STYLE_ID_PTR   + 1, LV_STYLE_ATTR_NONE),

    LV_STYLE_PROP_INIT(LV_STYLE_TEXT_LETTER_SPACE,  0x8, LV_STYLE_ID_VALUE + 0, LV_STYLE_ATTR_INHERIT),
    LV_STYLE_PROP_INIT(LV_STYLE_TEXT_LINE_SPACE,    0x8, LV_STYLE_ID_VALUE + 1, LV_STYLE_ATTR_INHERIT),
    LV_STYLE_PROP_INIT(LV_STYLE_TEXT_UNDERLINE,     0x8, LV_STYLE_ID_VALUE + 2, LV_STYLE_ATTR_INHERIT),
    LV_STYLE_PROP_INIT(LV_STYLE_TEXT_STRIKETHROUGH, 0x8, LV_STYLE_ID_VALUE + 3, LV_STYLE_ATTR_INHERIT),
    LV_STYLE_PROP_INIT(LV_STYLE_TEXT_BLEND_MODE,    0x8, LV_STYLE_ID_VALUE + 4, LV_STYLE_ATTR_INHERIT),
    LV_STYLE_PROP_INIT(LV_STYLE_TEXT_COLOR,         0x8, LV_STYLE_ID_COLOR + 0, LV_STYLE_ATTR_INHERIT),
    LV_STYLE_PROP_INIT(LV_STYLE_TEXT_SEL_COLOR,     0x8, LV_STYLE_ID_COLOR + 1, LV_STYLE_ATTR_INHERIT),
    LV_STYLE_PROP_INIT(LV_STYLE_TEXT_OPA,           0x8, LV_STYLE_ID_OPA   + 0, LV_STYLE_ATTR_INHERIT),
    LV_STYLE_PROP_INIT(LV_STYLE_TEXT_FONT,          0x8, LV_STYLE_ID_PTR   + 0, LV_STYLE_ATTR_INHERIT),

    LV_STYLE_PROP_INIT(LV_STYLE_LINE_WIDTH,         0x9, LV_STYLE_ID_VALUE + 0, LV_STYLE_ATTR_NONE),
    LV_STYLE_PROP_INIT(LV_STYLE_LINE_BLEND_MODE,    0x9, LV_STYLE_ID_VALUE + 1, LV_STYLE_ATTR_NONE),
    LV_STYLE_PROP_INIT(LV_STYLE_LINE_DASH_WIDTH,    0x9, LV_STYLE_ID_VALUE + 2, LV_STYLE_ATTR_NONE),
    LV_STYLE_PROP_INIT(LV_STYLE_LINE_DASH_GAP,      0x9, LV_STYLE_ID_VALUE + 3, LV_STYLE_ATTR_NONE),
    LV_STYLE_PROP_INIT(LV_STYLE_LINE_ROUNDED,       0x9, LV_STYLE_ID_VALUE + 4, LV_STYLE_ATTR_NONE),
    LV_STYLE_PROP_INIT(LV_STYLE_LINE_COLOR,         0x9, LV_STYLE_ID_COLOR + 0, LV_STYLE_ATTR_NONE),
    LV_STYLE_PROP_INIT(LV_STYLE_LINE_OPA,           0x9, LV_STYLE_ID_OPA   + 0, LV_STYLE_ATTR_NONE),

    LV_STYLE_PROP_INIT(LV_STYLE_IMAGE_BLEND_MODE,   0xA, LV_STYLE_ID_VALUE + 0, LV_STYLE_ATTR_INHERIT),
    LV_STYLE_PROP_INIT(LV_STYLE_IMAGE_RECOLOR,      0xA, LV_STYLE_ID_COLOR + 0, LV_STYLE_ATTR_INHERIT),
    LV_STYLE_PROP_INIT(LV_STYLE_IMAGE_OPA,          0xA, LV_STYLE_ID_OPA   + 0, LV_STYLE_ATTR_INHERIT),
    LV_STYLE_PROP_INIT(LV_STYLE_IMAGE_RECOLOR_OPA,  0xA, LV_STYLE_ID_OPA   + 1, LV_STYLE_ATTR_INHERIT),

    LV_STYLE_PROP_INIT(LV_STYLE_SCALE_WIDTH,         0xB, LV_STYLE_ID_VALUE + 0, LV_STYLE_ATTR_NONE),
    LV_STYLE_PROP_INIT(LV_STYLE_SCALE_BORDER_WIDTH,     0xB, LV_STYLE_ID_VALUE + 1, LV_STYLE_ATTR_NONE),
    LV_STYLE_PROP_INIT(LV_STYLE_SCALE_END_BORDER_WIDTH, 0xB, LV_STYLE_ID_VALUE + 2, LV_STYLE_ATTR_NONE),
    LV_STYLE_PROP_INIT(LV_STYLE_SCALE_END_LINE_WIDTH, 0xB, LV_STYLE_ID_VALUE + 3, LV_STYLE_ATTR_NONE),
    LV_STYLE_PROP_INIT(LV_STYLE_SCALE_COLOR,         0xB, LV_STYLE_ID_COLOR + 0, LV_STYLE_ATTR_NONE),
    LV_STYLE_PROP_INIT(LV_STYLE_SCALE_GRAD_COLOR,    0xB, LV_STYLE_ID_COLOR + 1, LV_STYLE_ATTR_NONE),
    LV_STYLE_PROP_INIT(LV_STYLE_SCALE_END_COLOR,     0xB, LV_STYLE_ID_COLOR + 2, LV_STYLE_ATTR_NONE),
};

typedef uint16_t lv_style_property_t;

#define LV_STYLE_STATE_POS       8
#define LV_STYLE_STATE_MASK      0x7F00

typedef uint16_t lv_style_state_t;

typedef struct {
    uint8_t * map;
#if LV_USE_ASSERT_STYLE
    uint32_t sentinel;
#endif
}lv_style_t;

typedef int16_t lv_style_int_t;


typedef struct {
    lv_style_t ** style_list;
#if LV_USE_ASSERT_STYLE
    uint32_t sentinel;
#endif
    uint8_t style_cnt;
    uint8_t has_local   :1;
}lv_style_list_t;

/**********************
 * GLOBAL PROTOTYPES
 **********************/

/**
 * Initialize a style
 * @param style pointer to a style to initialize
 */
void lv_style_init(lv_style_t * style);

/**
 * Copy a style with all its properties
 * @param style_dest pointer to the destination style. (Should be initialized with `lv_style_init()`)
 * @param style_src pointer to the source (to copy )style
 */
void lv_style_copy(lv_style_t * style_dest, const lv_style_t * style_src);

/**
 * Initialize a style list
 * @param list a style list to initialize
 */
void lv_style_list_init(lv_style_list_t * list);

/**
 * Copy a style list with all its styles and local style properties
 * @param list_dest pointer to the destination style list. (should be initialized with `lv_style_list_init()`)
 * @param list_src pointer to the source (to copy) style list.
 */
void lv_style_list_copy(lv_style_list_t * list_dest, const lv_style_list_t * list_src);

/**
 * Add a style to a style list.
 * Only the the style pointer will be saved so the shouldn't be a local variable.
 * (It should be static, global or dynamically allocated)
 * @param list pointer to a style list
 * @param style pointer to a style to add
 */
void lv_style_list_add_style(lv_style_list_t * list, lv_style_t * style);

/**
 * Remove a style from a style list
 * @param style_list pointer to a style list
 * @param style pointer to a style to remove
 */
void lv_style_list_remove_style(lv_style_list_t * list, lv_style_t * class);

/**
 * Remove all styles added from style list, clear the local style and free all allocated memories
 * @param list pointer to a style list.
 */
void lv_style_list_reset(lv_style_list_t * style_list);

static inline lv_style_t * lv_style_list_get_style(lv_style_list_t * list, uint8_t id)
{
    if(list->style_cnt == 0 || id >= list->style_cnt) return NULL;

    return list->style_list[id];
}

/**
 * Clear all properties from a style and all allocated memories.
 * @param style pointer to a style
 */
void lv_style_reset(lv_style_t * style);

/**
 * Get the size of the properties in a style in bytes
 * @param style pointer to a style
 * @return size of the properties in bytes
 */
uint16_t lv_style_get_mem_size(const lv_style_t * style);

/**
 * Copy a style to an other
 * @param dest pointer to the destination style
 * @param src pointer to the source style
 */
void lv_style_copy(lv_style_t * dest, const lv_style_t * src);

/**
 * Set an integer typed property in a style.
 * @param style pointer to a style where the property should be set
 * @param prop a style property ORed with a state.
 * E.g. `LV_STYLE_BORDER_WIDTH | (LV_STATE_PRESSED << LV_STYLE_STATE_POS)`
 * @param value the value to set
 * @note shouldn't be used directly. Use the specific property set functions instead.
 *       For example: `lv_style_set_border_width()`
 * @note for performance reasons it's not checked if the property really has integer type
 */
void _lv_style_set_int(lv_style_t * style, lv_style_property_t prop, lv_style_int_t value);

/**
 * Set a color typed property in a style.
 * @param style pointer to a style where the property should be set
 * @param prop a style property ORed with a state.
 * E.g. `LV_STYLE_BORDER_COLOR | (LV_STATE_PRESSED << LV_STYLE_STATE_POS)`
 * @param value the value to set
 * @note shouldn't be used directly. Use the specific property set functions instead.
 *       For example: `lv_style_set_border_color()`
 * @note for performance reasons it's not checked if the property really has color type
 */
void _lv_style_set_color(lv_style_t * style, lv_style_property_t prop, lv_color_t color);

/**
 * Set an opacity typed property in a style.
 * @param style pointer to a style where the property should be set
 * @param prop a style property ORed with a state.
 * E.g. `LV_STYLE_BORDER_OPA | (LV_STATE_PRESSED << LV_STYLE_STATE_POS)`
 * @param value the value to set
 * @note shouldn't be used directly. Use the specific property set functions instead.
 *       For example: `lv_style_set_border_opa()`
 * @note for performance reasons it's not checked if the property really has opacity type
 */
void _lv_style_set_opa(lv_style_t * style, lv_style_property_t prop, lv_opa_t opa);

/**
 * Set a pointer typed property in a style.
 * @param style pointer to a style where the property should be set
 * @param prop a style property ORed with a state.
 * E.g. `LV_STYLE_TEXT_POINTER | (LV_STATE_PRESSED << LV_STYLE_STATE_POS)`
 * @param value the value to set
 * @note shouldn't be used directly. Use the specific property set functions instead.
 *       For example: `lv_style_set_border_width()`
 * @note for performance reasons it's not checked if the property really has pointer type
 */
void _lv_style_set_ptr(lv_style_t * style, lv_style_property_t prop, const void * p);

/**
 * Get an integer typed property from a style.
 * @param style pointer to a style from where the property should be get
 * @param prop a style property ORed with a state.
 * E.g. `LV_STYLE_BORDER_WIDTH | (LV_STATE_PRESSED << LV_STYLE_STATE_POS)`
 * @param res pointer to a buffer to store the result value
 * @return -1: the property wasn't found in the style.
 *         The matching state bits of the desired state (in `prop`) and the best matching property's state
 *         Higher value means match in higher precedence state.
 * @note shouldn't be used directly. Use the specific property get functions instead.
 *       For example: `lv_style_get_border_width()`
 * @note for performance reasons it's not checked if the property really has integer type
 */
int16_t _lv_style_get_int(const lv_style_t * style, lv_style_property_t prop, lv_style_int_t * res);

/**
 * Get a color typed property from a style.
 * @param style pointer to a style from where the property should be get
 * @param prop a style property ORed with a state.
 * E.g. `LV_STYLE_BORDER_COLOR | (LV_STATE_PRESSED << LV_STYLE_STATE_POS)`
 * @param res pointer to a buffer to store the result value
 * @return -1: the property wasn't found in the style.
 *         The matching state bits of the desired state (in `prop`) and the best matching property's state
 *         Higher value means match in higher precedence state.
 * @note shouldn't be used directly. Use the specific property get functions instead.
 *       For example: `lv_style_get_border_color()`
 * @note for performance reasons it's not checked if the property really has color type
 */
int16_t _lv_style_get_color(const lv_style_t * style, lv_style_property_t prop, lv_color_t * res);

/**
 * Get an opacity typed property from a style.
 * @param style pointer to a style from where the property should be get
 * @param prop a style property ORed with a state.
 * E.g. `LV_STYLE_BORDER_OPA | (LV_STATE_PRESSED << LV_STYLE_STATE_POS)`
 * @param res pointer to a buffer to store the result value
 * @return -1: the property wasn't found in the style.
 *         The matching state bits of the desired state (in `prop`) and the best matching property's state
 *         Higher value means match in higher precedence state.
 * @note shouldn't be used directly. Use the specific property get functions instead.
 *       For example: `lv_style_get_border_opa()`
 * @note for performance reasons it's not checked if the property really has opacity type
 */
int16_t _lv_style_get_opa(const lv_style_t * style, lv_style_property_t prop, lv_opa_t * res);

/**
 * Get a pointer typed property from a style.
 * @param style pointer to a style from where the property should be get
 * @param prop a style property ORed with a state.
 * E.g. `LV_STYLE_TEXT_FONT | (LV_STATE_PRESSED << LV_STYLE_STATE_POS)`
 * @param res pointer to a buffer to store the result value
 * @return -1: the property wasn't found in the style.
 *         The matching state bits of the desired state (in `prop`) and the best matching property's state
 *         Higher value means match in higher precedence state.
 * @note shouldn't be used directly. Use the specific property get functions instead.
 *       For example: `lv_style_get_text_font()`
 * @note for performance reasons it's not checked if the property really has pointer type
 */
int16_t _lv_style_get_ptr(const lv_style_t * style, lv_style_property_t prop, void ** res);

/**
 * Set a local integer typed property in a style list.
 * @param list pointer to a style list where the local property should be set
 * @param prop a style property ORed with a state.
 * E.g. `LV_STYLE_BORDER_WIDTH | (LV_STATE_PRESSED << LV_STYLE_STATE_POS)`
 * @param value the value to set
 * @note for performance reasons it's not checked if the property really has integer type
 */
void lv_style_list_set_local_int(lv_style_list_t * list, lv_style_property_t prop, lv_style_int_t value);

/**
 * Set a local color typed property in a style list.
 * @param list pointer to a style list where the local property should be set
 * @param prop a style property ORed with a state.
 * E.g. `LV_STYLE_BORDER_COLOR | (LV_STATE_PRESSED << LV_STYLE_STATE_POS)`
 * @param value the value to set
 * @note for performance reasons it's not checked if the property really has color type
 */
void lv_style_list_set_local_color(lv_style_list_t * list, lv_style_property_t prop, lv_color_t value);

/**
 * Set a local opacity typed property in a style list.
 * @param list pointer to a style list where the local property should be set
 * @param prop a style property ORed with a state.
 * E.g. `LV_STYLE_BORDER_OPA | (LV_STATE_PRESSED << LV_STYLE_STATE_POS)`
 * @param value the value to set
 * @note for performance reasons it's not checked if the property really has opacity type
 */
void lv_style_list_set_local_opa(lv_style_list_t * list, lv_style_property_t prop, lv_opa_t value);

/**
 * Set a local pointer typed property in a style list.
 * @param list pointer to a style list where the local property should be set
 * @param prop a style property ORed with a state.
 * E.g. `LV_STYLE_TEXT_FONT | (LV_STATE_PRESSED << LV_STYLE_STATE_POS)`
 * @param value the value to set
 * @note for performance reasons it's not checked if the property really has pointer type
 */
void lv_style_list_set_local_ptr(lv_style_list_t * list, lv_style_property_t prop, const void * value);

/**
 * Get an integer typed property from a style list.
 * It will return the property which match best with given state.
 * @param list pointer to a style list from where the property should be get
 * @param prop a style property ORed with a state.
 * E.g. `LV_STYLE_BORDER_WIDTH | (LV_STATE_PRESSED << LV_STYLE_STATE_POS)`
 * @param res pointer to a buffer to store the result
 * @return LV_RES_OK: there was a matching property in the list
 *         LV_RES_INV: there was NO matching property in the list
 * @note for performance reasons it's not checked if the property really has integer type
 */
lv_res_t lv_style_list_get_int(lv_style_list_t * list, lv_style_property_t prop, lv_style_int_t * res);

/**
 * Get a color typed property from a style list.
 * It will return the property which match best with given state.
 * @param list pointer to a style list from where the property should be get
 * @param prop a style property ORed with a state.
 * E.g. `LV_STYLE_BORDER_COLOR | (LV_STATE_PRESSED << LV_STYLE_STATE_POS)`
 * @param res pointer to a buffer to store the result
 * @return LV_RES_OK: there was a matching property in the list
 *         LV_RES_INV: there was NO matching property in the list
 * @note for performance reasons it's not checked if the property really has color type
 */
lv_res_t lv_style_list_get_color(lv_style_list_t * list, lv_style_property_t prop, lv_color_t * res);


/**
 * Get an opacity typed property from a style list.
 * It will return the property which match best with given state.
 * @param list pointer to a style list from where the property should be get
 * @param prop a style property ORed with a state.
 * E.g. `LV_STYLE_BORDER_OPA | (LV_STATE_PRESSED << LV_STYLE_STATE_POS)`
 * @param res pointer to a buffer to store the result
 * @return LV_RES_OK: there was a matching property in the list
 *         LV_RES_INV: there was NO matching property in the list
 * @note for performance reasons it's not checked if the property really has opacity type
 */
lv_res_t lv_style_list_get_opa(lv_style_list_t * list, lv_style_property_t prop, lv_opa_t * res);

/**
 * Get a pointer typed property from a style list.
 * It will return the property which match best with given state.
 * @param list pointer to a style list from where the property should be get
 * @param prop a style property ORed with a state.
 * E.g. `LV_STYLE_TEXT_FONT | (LV_STATE_PRESSED << LV_STYLE_STATE_POS)`
 * @param res pointer to a buffer to store the result
 * @return LV_RES_OK: there was a matching property in the list
 *         LV_RES_INV: there was NO matching property in the list
 * @note for performance reasons it's not checked if the property really has pointer type
 */
lv_res_t lv_style_list_get_ptr(lv_style_list_t * list, lv_style_property_t prop, void ** res);

/*************************
 *    GLOBAL VARIABLES
 *************************/

/**********************
 *      MACROS
 **********************/

/**
 * Create and initialize a `static` style
 * Example:
 *     LV_STYLE_CREATE(my_style, &style_to_copy);
 *   is equivalent to
 *     static lv_style_t my_style;
 *     lv_style_init(&my_style);
 *     lv_style_copy(&my_style, &style_to_copy);
 */
#define LV_STYLE_CREATE(name, copy_p) static lv_style_t name; lv_style_init(&name); lv_style_copy(&name, copy);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /*LV_STYLE_H*/
