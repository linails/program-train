/*
 * Progarm Name: user.c
 * Created Time: 2017-02-10 16:55:00
 * Last modified: 2017-02-13 14:13:02
 * @author: minphone.linails linails@foxmail.com 
 */

#include "user.h"
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

/*
 * Note :
 *  
 *  用户信息对于服务器程序的安全性来说是很重要的，大部分的服务器就必须以 root 身份启动
 *  但不能以 root 身份运行
 *
 *  #include <sys/types.h>
 *  #include <unistd.h>
 *
 *  UID  : 真实用户ID
 *  EUID : 有效用户ID
 *  GID  : 真实组ID
 *  EGID : 有效组ID
 *
 *  uid_t getuid();
 *  uid_t geteuid();
 *  gid_t getgid();
 *  gid_t getegid();
 *
 *  int setuid(uid_t uid);
 *  int seteuid(uid_t uid);
 *  int setgid(gid_t gid);
 *  int setegid(gid_t gid);
 *
 * */

int user(void)
{
    int ret = 0;

    /* 
     * Note :
     *  01. real user id (uid) : 实际用户ID，指的是进程执行者是谁
     *  02. effective user id (euid) : 有效用户ID，指进程执行时对文件的访问权限
     *  03. saved set-user-id (saved uid) : 保存设置用户ID，是进程刚开始执行时，euid 的副本
     *
     *  chmod u+s filename 设置SUID位
     *  chmod u-s filename 去掉SUID位
     *  chmod g+s filename 设置SGID位
     *  chmod g-s filename 去掉SGID位
     * */
    uid_t uid = getuid();
    uid_t euid= geteuid();
    gid_t gid = getgid();
    gid_t egid= getegid();

    printf("userid is %d, effective userid is: %d\n", uid, euid);
    printf("gid is %d, effective gid is : %d \n", gid, egid);

    return ret;
}

/*
 * 以 root 身份启动后，切换到普通用户
 * */
int switch_to_user(uid_t user_id, gid_t gp_id)
{
    /* 
     * check 目标用户不是 root
     * */
    if((0 == user_id) && (0 == gp_id)) return -1;

    /* 
     * check 当前用户是合法用户：root 或者 目标用户
     * */
    gid_t gid = getgid();
    uid_t uid = getuid();
    printf("gid = %d - uid = %d\n", gid, uid);
    if(((0 != gid) || (0 != uid)) && ((gid != gp_id) || (uid != user_id))) return -1;

    if(0 != uid) return 0;

    /* 
     * 切换到目标用户
     * */
    if((0 > setgid(gp_id)) || (0 > setuid(user_id))) return -1;

    return 0;
}

