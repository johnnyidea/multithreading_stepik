#include <iostream>
#include <algorithm>

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sstream>
#include <cstring>
#include <climits>
#include <fstream>

//who | sort | uniq -c | sort -nk1

using namespace std;

void trim_cmd(string& cmd)
{
    if (cmd[0] == ' ')
        cmd.erase(0, 1);
    if (cmd[cmd.size() - 1] == ' ')
        cmd.erase(cmd.size() - 1, 1);
}

void handle_process()
{
    string cmds;// {"who | sort | uniq -c | sort -nk1"};
    string data;
    getline(cin, cmds);
    istringstream stream_cmds(cmds);

    for (string cmd; getline(stream_cmds, cmd, '|');)
    {
        trim_cmd(cmd);

        int major_pipe[2];
        int minor_pipe[2];

        int major_pipe_res = pipe(major_pipe);
        int minor_pipe_res = pipe(minor_pipe);

        if (major_pipe_res == -1)
        {
            perror("Major pipe error");
            exit(EXIT_FAILURE);
        }

        if (minor_pipe_res == -1)
        {
            perror("Minor pipe error");
            exit(EXIT_FAILURE);
        }

        int proc_pid = fork();

        if (proc_pid < 0)
        {
            perror("fork error");
            exit(EXIT_FAILURE);
        } else if (proc_pid == 0)
        {
            if (cmd.compare("who") != 0)
            {
                close(STDIN_FILENO);
                dup2(minor_pipe[0], STDIN_FILENO);
                close(minor_pipe[1]);
                close(minor_pipe[0]);
            }

            close(STDOUT_FILENO);
            dup2(major_pipe[1], STDOUT_FILENO);
            close(major_pipe[1]);
            close(major_pipe[0]);

            cerr << cmd << endl;

            auto num_args = count(cmd.begin(), cmd.end(), ' ');
            char* c_cmds[num_args + 2];
            c_cmds[num_args + 1] = NULL;

            if (num_args == 0)
            {
                c_cmds[0] = (char *)(cmd.c_str());
            } else
            {
                auto pos = cmd.find(' ');
                c_cmds[0] = (char *)cmd.substr(0, pos).c_str();
                c_cmds[1] = (char *)cmd.substr(pos + 1, cmd.size() - 1).c_str();
            }

            execvp(c_cmds[0],c_cmds);
        } else
        {
            if (cmd.compare("who") != 0)
            {
                write(minor_pipe[1], data.c_str(), data.size());
                close(minor_pipe[1]);
                close(minor_pipe[0]);
            }

            close(STDIN_FILENO);
            dup2(major_pipe[0], STDIN_FILENO);
            close(major_pipe[1]);
            close(major_pipe[0]);

            char buf[PIPE_BUF];

            memset(buf, 0, PIPE_BUF);
            read(STDIN_FILENO, buf, PIPE_BUF);

            data = string(buf);
        }
    }

//    ofstream out("/home/box/result.out");
    ofstream out("/home/rene/education/multithreading_stepik/week5/active_users_num/result.out");
    out << data.c_str();
    out.close();

}

int main(int argc, char** argv)
{
    handle_process();
    return 0;
}


