#coding:utf-8
#__author__:yanglong
#data:2019-4-3

import re
import sys,os
import pexpect
import commands,socket

def execute(cmd):
	(status,output)=commands.getstatusoutput(cmd)
	return (status,output)

def creat_local_key():
	print 'start create local key'
	(status,oupput)=execute('rm -rf /root/.ssh')
	if status!=0:
		return (status,'rm ssh file failed')
	node1=pexpect.spawn("ssh-keygen -t rsa")
	node1.expect('Enter')
	node1.sendline()
	node1.expect('Enter')
	node1.sendline()
	node1.expect('Enter')
	node1.sendline()
	node1.interact()
	node1.close(force=True)

	(status,output)=execute('cp /root/.ssh/id_rsa.pub /root/.ssh/local.key')
	(status,output)=execute('cat /root/.ssh/local.key >> /root/.ssh/authorized_keys')
	(status,output)=execute('chmod 755 /root/.ssh')

	if os.path.exists('/root/.ssh/local.key'):
		print 'create local key success'
	else:
		print 'create local key failed'
		return -1
	return 0

def creat_other_key(ips,pwds):
	local_ip=get_local_ip()
	#print "local_ip is %s"%local_ip
	i=-1
	for ip in ips:
		i=i+1
		if ip!=local_ip: 
			print 'start create %s key'%ip
			del_ssh=pexpect.spawn("ssh root@%s rm -rf /root/.ssh"%ip)
			status=del_ssh.expect_exact(['(yes/no)?','password:',pexpect.TIMEOUT])
			if status==0:
				del_ssh.sendline('yes')
				del_ssh.expect('.*sword:')
				del_ssh.sendline(pwds[i])
				del_ssh.interact()
				del_ssh.close(force=True)
			elif status==1:
				del_ssh.sendline(pwds[i])
				del_ssh.interact()
				del_ssh.close(force=True)
			else:
				print "ssh %s timeout"%ip
				return -1

			pro=pexpect.spawn("ssh root@%s ssh-keygen -t rsa"%ip)
			pro.expect('.*sword:')
			pro.sendline(pwds[i])
			pro.expect('Enter')
			pro.sendline()
			pro.expect('Enter')
			pro.sendline()
			pro.expect('Enter')
			pro.sendline()
			pro.interact()
			pro.close(force=True)
			
			text=pexpect.spawn("scp root@%s:/root/.ssh/id_rsa.pub /root/.ssh/%s.key"%(ip,ip))
			text.expect('.*sword:')
			text.sendline(pwds[i])
			text.interact()
			text.close(force=True)

			mod=pexpect.spawn("ssh root@%s chmod 755 /root/.ssh"%ip)
			mod.expect('.*sword:')
			mod.sendline(pwds[i])
			mod.interact()
			mod.close(force=True)
			execute('cat /root/.ssh/%s.key >> /root/.ssh/authorized_keys'%ip)
			execute('chmod 600 /root/.ssh/*')

			if os.path.exists('/root/.ssh/%s.key'%ip):
				print 'create %s key success'%ip
			else:
				print 'create %s key failed'%ip
				return -1
	return 0

def send_author_key(ips,pwds):
	local_ip=get_local_ip()
	i=-1
	for ip in ips:
		i=i+1
		if ip!=local_ip:
			print 'start send author_key to %s'%ip
			try:
				auth=pexpect.spawn("scp /root/.ssh/authorized_keys root@%s:/root/.ssh/"%ip)
				auth.expect('.*sword:')
				auth.sendline(pwds[i])
				auth.interact()
				auth.close(force=True)
			except:
				print 'send author_key to %s failed'%ip
				return -1
			else:
				print 'send author_key to %s success'%ip
				
			(status,output)=execute("ssh root@%s chmod 600 /root/.ssh/*"%ip)
			(status,output)=execute("ssh root@%s chmod -R 600 /etc/ssh/*"%ip)
			(status,output)=execute("ssh root@%s systemctl restart sshd"%ip)

		else:
			auth=pexpect.spawn("scp /root/.ssh/authorized_keys root@%s:/root/.ssh/"%ip)
			status=auth.expect_exact(['(yes/no)?','password',pexpect.EOF])
			if status==0:
				auth.sendline('yes')
				tag=auth.expect(['.*sword:',pexpect.EOF])
				if tag==0:
					auth.sendline(pwds[i])
					auth.interact()
					auth.close(force=True)
				else:
					auth.interact()
					auth.close(force=True)
					
			elif status==1:
				auth.sendline(pwds[i])
				auth.interact()
				auth.close(force=True)
			else:
				auth.interact()
				auth.close(force=True)
				
	return 0

def send_hosts(ips,nodes):
	init=[
		"127.0.0.1   localhost localhost.localdomain localhost4 localhost4.localdomain4\n",
		"::1         localhost localhost.localdomain localhost6 localhost6.localdomain6\n"
		]
	with open('/etc/hosts','w+') as hosts:
		hosts.writelines(init)

	local_ip=get_local_ip()
	i=-1
	for ip in ips:
		i=i+1
		#print node
		(status,output)=execute("ssh root@%s hostnamectl --static set-hostname %s"%(ip,nodes[i]))
		if status!=0:
			print 'set-hostname %s failed:'%nodes[i],output
			return -1
		else:
			print 'set-hostname %s success'%nodes[i]
			
		data=ip+' '+nodes[i]+'\n'
		with open('/etc/hosts','a+') as hosts:
			hosts.write(data)

	for ip in ips:
		if local_ip!=ip:
			(status,output)=execute("scp /etc/hosts root@%s:/etc/hosts"%ip)
			if status!=0:
				print 'send hosts to %s failed'%ip,output
				return -1
			else:
				print 'send hosts to %s success'%ip
	return 0

def get_local_ip():
	'''
	csock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
	csock.connect(('8.8.8.8', 80))
	(addr, port) = csock.getsockname()
	csock.close()
	'''
	(ips,nodes,pwds)=read_file()
	for ip in ips:
		(status,output)=execute("ip a|grep %s"%ip)
		if status==0:
			return ip
	print "no exite local_ip"
	sys.exit()

def disableselinux(nodes):
	data=[
		'SELINUX=disabled\n',
		'SELINUXTYPE=targeted\n'
		]
	with open('/etc/selinux/config','w+') as sel:
		sel.writelines(data)

	for node in nodes:
		print 'start config %s selinux'%node
		hosts=pexpect.spawn("scp /etc/selinux/config root@%s:/etc/selinux/config"%node)
		status=hosts.expect_exact(['(yes/no)?',pexpect.EOF])
		if status==0:
			hosts.sendline('yes')
			hosts.interact()
			hosts.close(force=True)
		else:
			hosts.interact()
			hosts.close(force=True)
			
		try:
			(status,output)=execute("ssh root@%s setenforce 0"%node)
			(status,output)=execute("ssh root@%s systemctl stop filewalld"%node)

			(status,output)=execute("ssh root@%s systemctl disable firewalld"%node)
			(status,output)=execute("ssh root@%s systemctl stop NetworkManager"%node)

			(status,output)=execute("ssh root@%s systemctl disable NetworkManager"%node)
			(status,output)=execute("ssh root@%s chmod 600 /etc/ssh/*"%node)

			(status,output)=execute("ssh root@%s systemctl restart sshd"%node)
		except:
			print 'config %s selinux failed'%node
			return -1
		else:
			print 'config %s selinux success'%node
	return 0		

def network_file(ips,nodes):
	local_ip=get_local_ip()
	i=-1
	for ip in ips:
		i=i+1
		data=[
			"""NETWORKING="yes"\n""",
			"""HOSTNAME="%s"\n"""%nodes[i]
			]
		if ip==local_ip:
			with open('/etc/sysconfig/network','w+') as loc_net:
				loc_net.writelines(data)
		else:
			path='/etc/sysconfig/%s.tep'%ip
			with open(path,'w+') as loc_net:
				loc_net.writelines(data)
			
			(status,output)=execute("scp /etc/sysconfig/%s.tep root@%s:/etc/sysconfig/network"%(ip,ip))
			if status!=0:
				print 'config %s network_file failed'%ip
				return -1
			else:
				print 'config %s network_file success'%ip

	(status,output)=execute('rm -rf /etc/sysconfig/*.tep')
	return 0

def send_known_hosts(ips):
	local_ip=get_local_ip()
	for ip in ips:
		if ip!=local_ip:
			(status,output)=execute("scp /root/.ssh/known_hosts root@%s:/root/.ssh/"%ip)
			if status!=0:
				print "%s send known_hosts fail"%ip
				return -1
			print "send known_hosts to %s success"%ip
	return 0

def is_ip(addr):			
	if str(addr).count(".")!=3:
		return False
	try:
		socket.inet_aton(str(addr))
		return True
	except socket.error:
		return False

def hostname_is_valid(ips,names):
	set_list=set(names)
	same_name_list=[]
	tag=0
	if len(set_list)!=len(names):
		for na in names:
			idl=[i for i,name in enumerate(names) if name==na]
			if len(idl)!=1 and idl not in same_name_list:
				same_name_list.append(idl)
		#print same_name_list
		for same_name in same_name_list:
			for i in same_name:
				print ips[i],
			print ':hostname is same,please modify hostname'
		return -1

	for ip,name in zip(ips,names):
		if re.match('^[0-9a-z]+$',name)==None:
			print '%s hostname : %s is invalid,only number or lowercase'%(ip,name)
			tag=tag+1
	if tag:
		return -1
	return 0

def read_file():
	with open('./ips.txt','r') as txt:
		data=txt.readlines()
		ips=[]
		nodes=[]
		pwds=[]
		for i in data:
			msg=i.strip().split(':')
			#print msg
			if msg[0]=='':
				print "file exists empty line"
				sys.exit()
			else:
				status=is_ip(msg[0])
				if status:
					ips.append(msg[0])
				else:
					print "%s is invalid"%msg[0]
					sys.exit()

			if len(msg)<2 or msg[1]=='':
				nodename='node'+(msg[0].split('.'))[3]
				nodes.append(nodename)
			else:
				nodes.append(msg[1])
			if len(msg)<3 or msg[2]=='':
				pwds.append('daemon')
			else:
				pwds.append(msg[2])
	
	return (ips,nodes,pwds)
	
def run():
	(ips,nodes,pwds)=read_file()
	status=hostname_is_valid(ips,nodes)
	if status!=0:
		return -1

	status=creat_local_key()
	if status!=0:
		return -1

	status=creat_other_key(ips,pwds)
	if status!=0:
		return -1

	status=send_author_key(ips,pwds)
	if status!=0:
		return -1

	status=send_hosts(ips,nodes)
	if status!=0:
		return -1

	status=disableselinux(nodes)
	if status!=0:
		return -1

	status=network_file(ips,nodes)
	if status!=0:
		return -1

	status=send_known_hosts(ips)
	if status!=0:
		return -1
	print 'all node link success'

if __name__=="__main__":
	#print creat_local_key()
	#print creat_other_key('10.0.7.158')
	#print creat_other_key('10.0.7.222')
	#print send_author_key('10.0.7.158')
	#print send_author_key('10.0.7.222')
	#print send_hosts(['10.0.6.230','10.0.7.158','10.0.7.222'])
	#print disableselinux(['10.0.7.222'])
	#print get_local_ip()
	#print read_file()
	#hostname_is_valid(['10.0.7.222','10.0.7.158','10.0.7.82'],['node1','node2','node1'])
	run()
