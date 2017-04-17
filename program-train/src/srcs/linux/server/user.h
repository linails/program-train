/*
 * Progarm Name: user.h
 * Created Time: 2017-02-10 16:55:03
 * Last modified: 2017-02-13 13:45:08
 * @author: minphone.linails linails@foxmail.com 
 */

#ifndef _USER_H_
#define _USER_H_
#ifdef __cplusplus
extern "C" {
#endif

#include <sys/types.h>
#include <unistd.h>

extern int user(void);

extern int switch_to_user(uid_t user_id, gid_t gp_id);

#ifdef __cplusplus
}
#endif
#endif //_USER_H_

