# 引入需要使用到的库
# requests是一个提交http请求的常用的库。
from selenium import webdriver
import requests
from selenium.webdriver.common.action_chains import ActionChains
from selenium.webdriver.common.keys import Keys
from time import sleep
# lxml是一个解析html和xml文件格式的库
from lxml import etree
from selenium.webdriver.chrome.options import Options
chrome_driver_path="chromedriver.exe"
chrome_options = Options()

#chrome_options.add_argument('--headless')
chrome_options.add_argument('--disable-gpu')
driver = webdriver.Chrome(chrome_options=chrome_options, \
    executable_path= chrome_driver_path)
# 设置requests的header，这样发送的和请求正常的浏览器一样，很多服务器会验证header
driver.header = {'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) ' 
                        'Chrome/51.0.2704.63 Safari/537.36'}
# 这里向URL发送get请求，并获得返回的response
driver.get('https://piyao.sina.cn/')
tempname_and_goods=[]
for i in range(0,20):
    js = "var q=document.documentElement.scrollTop=1000000"
    driver.execute_script(js)
    sleep(8)
# response有state（200、404等）、header、content等字段，其中content字段是返回的内容，通常是html格式的。
response=driver.page_source
html = etree.HTML(response)
# 使用chrome的F12观察了返回的html的结构，复制了感兴趣的数据的xpath并根据特点自行修改
for i in range(1,30):
    time = html.xpath('//div[@class="zy_day" and position()='+str(i)+']/div[@class="day_date"]/text()')
    names = html.xpath('//div[@class="zy_day" and position()='+str(i)+']/div[@class="day_date"]/following-sibling::ul//div[@class="left_title"]/text()')
    goods = html.xpath('//div[@class="zy_day" and position()='+str(i)+']/div[@class="day_date"]/following-sibling::ul//div[@class="comment_text"]/text()')
# 把数据组合成元组的列表
    k=0
    for name in names:
        temp= [str(name),str(goods[k]),str(time)]
        k+=1
        tempname_and_goods.append(temp)
high_goods = sorted(tempname_and_goods, key=lambda x :int(x[1]))
high_goods.reverse()
# 打印结果
print(tempname_and_goods)
print("十大谣言：")
for x in high_goods[:10]:
    print('标题:', x[0], '\t','评论数：',x[1],'\t','日期:',x[2])