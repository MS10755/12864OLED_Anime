import sys
from os import system
import re


def help():
    print("Usage: python font_maker.py [bdf_file] [text_file] [font_name]")

def main():

    if(len(sys.argv) != 4):
        help()
        return
    bdf_file = sys.argv[1]
    text_file = sys.argv[2]
    font_name = sys.argv[3]

    if(text_file == "" or font_name == ""):
        help()
        return

    if bool(re.match(r'.*\.txt$',text_file)) == False:
        print("只支持txt文件的转换")
        return
    text_file = text_file.replace(".txt","")

    str_cmd = 'tools\iconv.exe -f utf-8 -t c99 ' + text_file + '.txt > ' + text_file + '.map'
    system(str_cmd)
    
    content = list()
    with open(text_file +'.map','r+') as f:
        content = str(f.read())
        content = content.replace("\n","")
        content = content.split("\\u")
        f.close()
    
    content.pop(0)
    content.sort()

    with open(text_file +'.map','r+') as f:
        f.truncate(0)
        f.write("32-128,\n")
        for codeing in content:
            f.write( "$"+ codeing + ",\n")
        f.close()
    str_cmd = "bdfconv.exe " + bdf_file + " -b 0 -f 1 -M "+text_file + ".map " + "-n " + font_name + " -o " + font_name + ".c"
    print(str_cmd)
    system(str_cmd)

if __name__ == '__main__':
    main()