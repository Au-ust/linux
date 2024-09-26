#include<iostream>
#include<string>
#include<vector>
#include<unistd.h>
#include<sys/types.h>
 class Channel{
    public:
    Channel(int wfd, pid_t id, const std::string &name):_wfd(wfd),_subprocessid(id),_name(name){}
    int Getfd(){
        return _wfd;
    }
    pid_t GetProcessId(){
        return _subprocessid;
    }
    std::string GetName(){
        return _name;
    }
    ~Channel(){}
    private:
        int _wfd;
        pid_t _subprocessid;
        std::string _name;
 };
 void work(int rfd){
    while(true){
        sleep(1);
    }
 }
int main(int argc,char* argv[])
{
    if(argc!=2){
        std::cerr<<"usage:"<<argv[0]<<"processnum"<<std::endl;
        return 1;
    }
    int num=std::stoi(argv[1]);
    std::vector<Channel>channels;
    for(int i=0;i<num;i++){
        int pipefd[2]={0};
        int n=pipe(pipefd);
        if(n<0){
            exit(1);
        }
        pid_t id =fork();
        if(id==0){
            close(pipefd[1]);
            work(pipefd[0]);
            close(pipefd[0]);
            exit(0);
        }
        std::string channel_name="Channel"+std::to_string(i);
        close(pipefd[0]);
        channels.push_back(Channel(pipefd[1],id,channel_name));
    }
    for(auto &channel:channels){
        std::cout << " ---------------------- " <<std::endl;
        std::cout << channel.GetName() << std::endl;
        std::cout << channel.Getfd() << std::endl;
        std::cout << channel.GetProcessId() << std::endl;
    }
    sleep(10);
    std::cout<<"over"<<std::endl;
    return 0;
}