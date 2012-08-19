#ifndef _APPNETPOST_PRIVATE_H_INCLUDED_
#define _APPNETPOST_PRIVATE_H_INCLUDED_

#ifdef __cplusplus
extern "C" {
#endif

#include <jansson.h>

AppNetPost*
_app_net_post_from_json (json_t *json);

#ifdef __cplusplus
};
#endif

#endif

