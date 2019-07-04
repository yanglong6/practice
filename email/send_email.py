#coding:utf-8
#__author__:yanglong
#__date__:2019.4.17

import smtplib
from email.mime.text import MIMEText as txt
from email.header import Header

sender="1160549687@qq.com"
receivers=["yang.long@datatom.com"]
pwd='pkzgqagwvshwfhgd'  #授权码

def send_msg(msg):
	msg=txt(msg,'plain','utf-8')
	msg['From']='通知'
	msg['To']='杨龙'
	msg['Subject']='更新提醒'
	try:
		smtp=smtplib.SMTP_SSL('smtp.qq.com',465)
		smtp.login(sender,pwd)
		smtp.sendmail(sender,receivers,msg.as_string())
		print '发送成功'
	except:
		print '发送失败'
	return 0	

if __name__=="__main__":
	send_msg()

