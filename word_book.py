#coding:utf-8
#__author__:yanglong
#__date__:2019.4.11

import datetime as time
import sys
import requests
import json
import pymongo

reload(sys)
sys.setdefaultencoding('utf-8')

api_url='http://dict-co.iciba.com/api/dictionary.php?key=E5F04B2930821D0BC354E4E832DBB292&type=json&w='

def current_time():
	dict_week={1:'一',2:'二',3:'三',4:'四',5:'五',6:'六',7:'日'}
	week=time.datetime.now().isoweekday()
	local_time=str(time.datetime.now().strftime('%Y-%m-%d')+':星期'+dict_week.get(week))
	return local_time

def check_all_chinese(check_str):
	for ch in unicode(check_str):
		if not (u'\u4e00' <= ch <= u'\u9fff'):
			return False
	return True

def put_word():
	while True:
		word=raw_input("输入要记录的单词(直接回车退出程序):\n").strip()
		if word=='':
			sys.exit()
		elif word.isalpha() or  check_all_chinese(word):
			return word
		else:
			print "输入单词格式错误，请重新输入！"

def total_word():
	with open("word.txt","a+") as txt:
		data=txt.readlines()
		total=len(data)
	return total
	
def is_exits(in_word):
	with open("word.txt","a+") as txt:
		for data in txt.readlines():
			ll=data.split(' ')
			if in_word==ll[0]:
				print "单词已存在"
				return -1
		else:
			return 0

def cord_word(in_word,info):
	status=is_exits(in_word)
	if status!=0:
		total=total_word()
		print "已记录 %d 个单词/词组\n"%total
		return -1
	else:
		data=in_word+"     "+current_time()+"     "+info+'\n'
		with open("word.txt","a+") as txt:
			txt.write(data)
		total=total_word()
		print "已记录 %d 个单词/词组\n"%total
		return 0

def translate(in_word):
	api=(api_url+in_word).strip()
	try:
		data=requests.get(api).json()
		#print json.dumps(data,sort_keys=True, indent=4, separators=(',', ': '))
	except:
		print "请求错误"
		return '',''
	symbols=data['symbols'][0]
	ph_en=symbols.get('ph_en')
	means=symbols.get('parts')
	if not means:
		print "未找到中文翻译"
		return '',''
	means_all=[]
	for m in means:
		means_all.append(m['part']+''.join(m['means'])+' | ')
	if ph_en:
		ph_en=ph_en.encode("utf-8")
		info=("["+ph_en+"] "+("".join(means_all)).encode("utf-8"))
	else:
		info="".join(means_all).encode("utf-8")
	print info
	return (ph_en,info)

def chinese_translate(in_word):
	api=api_url+in_word
	try:
		data=requests.get(api).json()
		#print json.dumps(data,sort_keys=True, indent=4, separators=(',', ': '))
	except:
		print "请求错误"
		return '',''
	symbols=data['symbols'][0]
	try:
		word_symbol=symbols.get('word_symbol')
		means=symbols.get('parts')[0].get("means")
	except:
		print "未找到英文翻译"
		return '',''
	else:
		if not means:
			print "未找到英文翻译"
			return '',''

	means_all=[]
	for m in means:
		means_all.append(m.get("word_mean")+',')
	if word_symbol:
		word_symbol=word_symbol.encode("utf-8")
		info=("["+word_symbol+"] "+("".join(means_all)).encode("utf-8"))
	else:
		info="".join(means_all).encode("utf-8")
	print info
	return (word_symbol,info)
	
def add_db(word,time,ph,info):
	my_client=pymongo.MongoClient("mongodb://10.0.6.57:27017/")
	db_list=my_client.list_database_names()
	mydb=my_client["word_book"]
	colist=mydb.list_collection_names()
	col=mydb["book"]
	data={"word":"","time":"","ph_en":"","info":""}
	data["word"]=word
	data["time"]=time
	data["ph_en"]=ph
	data["info"]=info
	try:
		col.insert_one(data)
	except:
		print "add mongodb failed"
		return -1
	else:
		print "add %s to mongodb success"%word
		return 0

def run():
	while True:
		word=put_word()
		status=check_all_chinese(word)
		if status:
			(ph_en,info)=chinese_translate(word)
		else:
			(ph_en,info)=translate(word)

		time=current_time()
		if ph_en or info:
			status=cord_word(word,info)
			if not status:
				add_db(word,time,ph_en,info)
	return 0

if __name__=="__main__":
	#print current_time()
	#put_word()
	#is_exits("hello")
	run()
	#translate(data)
	#chinese_translate(data)
	#add_db("4","3","2","1")
	#print check_all_chinese(raw_input())
