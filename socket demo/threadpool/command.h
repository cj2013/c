/*
 * command.h
 *
 *  Created on: 2018年3月8日
 *      Author: wang
 */

#ifndef SERVER_COMMAND_H_
#define SERVER_COMMAND_H_

class Command
{
public:
    int 	get_cmd();
    char* get_arg();
    void set_cmd(int cmd);
    void set_arg(char* arg);
private:
    int cmd_;
    char arg_[65];
};


#endif /* SERVER_COMMAND_H_ */
