#coding:utf-8
from flask import Flask,render_template,request,redirect,session

app = Flask(__name__)
app.secret_key = 'u2jksidjflsduwerjl'
app.debug = True

#登录
@app.route('/login',methods=['GET',"POST"])
def login():
    if request.method == 'GET':
        return render_template('login.html')
    user = request.form.get('user')
    pwd = request.form.get('pwd')

    if user == 'admin' and pwd == '123456':      
        session['user_info'] = user
        return redirect('/index')
    else:
        return render_template('login.html',msg =u'用户名或密码错误')

#首页
@app.route('/index',methods=['GET','POST'])
def index():
	users={
			"yy":"1111",
			"ll":"2222",
			"oo":"3333",
		}
	user_info=session.get("user_info")
	if not user_info:
		return redirect('/login')

	return render_template('detail.html',user_dict=users)

if __name__=="__main__":
	app.run('10.0.6.57',debug=True)
