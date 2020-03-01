#coding:utf-8
#__author__:yanglong
#__date__:2019.4.18

import requests
import send_email
import time
#from lxml import etree
common=''

url='http://d1.weather.com.cn/sk_2d/101270101.html?_=1556252165579'

def login():
	header={
	'Referer':"http://www.weather.com.cn/weather1d/101270101.shtml",
	'User-Agent':"Mozilla/5.0 (Windows NT 10.0; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/73.0.3683.103 Safari/537.36",
}

	respond=requests.get(url,headers=header)
	return respond.content

def get_time(respond):
	where=respond.find('{')
	data=respond[where:].strip()
	all_data=eval(data)["time"]
	
	print all_data
	return all_data

def run():
	while True:
		respond=login()
		data=get_time(respond)
		if data!=common:
			send_email.send_msg(data)
			global common
			common=data
		print "睡眠中......"
		time.sleep(60)
		
if __name__=="__main__":
	run()
