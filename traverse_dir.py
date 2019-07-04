#coding:utf-8
#__author__:yanglong
#__date__:2019.4.9

import os,fnmatch
import json

def traverse_dir(in_path,in_style):
	file_list={}
	for (root,dirnames,filenames) in os.walk(in_path):
		for filename in filenames:
			if fnmatch.fnmatch(filename,"*%s"%in_style):
				path=os.path.join(root,filename)
				file_list[filename]=path

	if file_list:
		print json.dumps(file_list,sort_keys=True, indent=4, separators=(',', ': '))
		return file_list
	print "no exits *%s file"%in_style
	return -1

def find_key(in_path,key_word):
	file_list=[]
	for (root,dirnames,filenames) in os.walk(in_path):
		for filename in filenames:
			path=os.path.join(root,filename)
			file_list.append(path)
	#print file_list
	result_list={}
	for each_file in file_list:
		with open(each_file,'r') as f:
			index_list=[]
			for index,line in enumerate(f.readlines()):
				if key_word in line:
					#print line
					index_list.append(index+1)
			if index_list:
				result_list[each_file]=index_list
	if result_list:
		print json.dumps(result_list,sort_keys=True, indent=4, separators=(',', ': '))
	else:
		print "未找到相关内容"
		return -1

def run():
	tag=raw_input("1:查找文件   2:查找文件内容\n请选择:")
	if tag=='1':
		path=raw_input('请输入文件夹的路径:')
		style=raw_input("请输入文件名或文件的格式,如'test.py','.txt':")
		traverse_dir(path,style)
	elif tag=='2':
		path=raw_input('请输入文件夹的路径:')
		keyword=raw_input("请输入查找的关键字:")
		find_key(path,keyword)
	else:
		print "输入错误！！！"
		

if __name__=="__main__":
	run()
