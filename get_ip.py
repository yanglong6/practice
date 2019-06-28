#coding:utf-8
#author:yanglong
#data:2019.5.12

import commands
import sys
import socket

def execute(cmd):
    (status,output)=commands.getstatusoutput(cmd)
    return (status,output)

def get_all_ip(output):
    ips=[]
    for ip in output.split('\n'):
        if is_ip(ip):
            ips.append(ip)
    if ips:
        return ips
    return -1

def is_ip(addr):
    if str(addr).count(".")!=3:
        return False
    try:
        socket.inet_aton(str(addr))
        return True
    except socket.error:
        return False

def run():
    (status,output)=execute("ip a | grep inet |awk -F '/' '{print $1}' \
                            |awk -F ' ' '{print $2}'")
    if status!=0:
        print "execute cmd error"
        return -1
    #print output

    ret=get_all_ip(output)
    if ret==-1:
        print "get ips failed"
        return -1
    else:
        return ret

if __name__=="__main__":
    print run()
