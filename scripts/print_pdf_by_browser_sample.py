#!/bin/python3

import time
import subprocess

# BROWSER = "google-chrome-unstable"


def getContent(content):
    startPos = content.find("<!-- anchor -->") + len("<!-- anchor -->") + 1
    return content[startPos:-1]


def genReport():
    # use ''' may cause invalid format
    base_content = "---\n" + \
        "layout: page\n" + \
        "title: 实验报告\n" + \
        "permalink: /report/\n" + \
        "---\n\n" + \
        "* TOC\n" + \
        "{:toc}\n\n" + \
        "---\n"

    try:
        index_file = open('index.md')
        software_file = open('software.md')
        hardware_file = open('hardware.md')
        download_file = open('download.md')
        report_file = open('report.md', 'w')

        index_content = "# 项目简介\n" + getContent(index_file.read()) + "\n"
        software_content = "# 软件部分\n" + getContent(software_file.read()) + "\n"
        hardware_content = "# 硬件部分\n" + getContent(hardware_file.read()) + "\n"
        download_content = "# 资源下载\n" + getContent(download_file.read()) + "\n"

        printScript = "<script type=\"text/javascript\">window.print()</script>\n"

        content = base_content + index_content + \
            hardware_content + software_content + download_content + printScript

        report_file.write(content)

    except Exception as e:
        raise

    finally:
        index_file.close()
        software_file.close()
        hardware_file.close()
        download_file.close()
        report_file.close()


def togglePrintPDF(boolean):
    try:
        # why dose this append to the file????
        # config_file = open('_config.yml', 'r+')
        config_file = open('_config.yml', 'r')
        config_content = config_file.read()
        config_file.close()
        if boolean:
            config_content = config_content.replace(
                "printPDF: false", "printPDF: true")
        else:
            config_content = config_content.replace(
                "printPDF: true", "printPDF: false")

        config_file = open('_config.yml', 'w')
        config_file.write(config_content)

    except Exception as e:
        raise
    finally:
        config_file.close()


# def insertScript():
#     script = "<script type=\"text/javascript\">window.print()</script>"
#     subprocess.Popen("sed -i \'$a\\" + script +
#                      "\' _site/report/index.html", shell=True)

if __name__ == '__main__':

    # Why dose it auto flush???
    # subprocess.call("cp _config.yml _config.yml.back2", shell=True)
    # subprocess.call("sed 's/true/false/g' _config.yml.back | > _config.yml", shell=True)
    # .....
    # os.system("cp _config.yml_back _config.yml")
    # os.system("rm _config.yml.back")
    # retcode = subprocess.call("ls -l",shell=True)
    # print(retcode)

    try:
        togglePrintPDF(True)
        genReport()

        p_jekyll = subprocess.Popen("jekyll serve", shell=True)
        time.sleep(5)

        print("-----------")
        print("[DO NOT] press Ctrl-C!! Process will terminate in 30s.")
        print("-----------")
        # insertScript()

        # p_browser = subprocess.Popen(
        #     BROWSER + " http://127.0.0.1:4000/kc/2016-12/C39/report", shell=True)

        # this will call default application to open under linux/osx
        p_browser = subprocess.Popen(
            "xdg-open http://127.0.0.1:4000/kc/2016-12/C39/report", shell=True)

        time.sleep(30)
        print("Timeout. Kill process.")
    except Exception as e:
        raise
    finally:
        togglePrintPDF(False)
        # clear generated pages
        subprocess.Popen("rm -rf _site/", shell=True)
        subprocess.Popen("rm report.md", shell=True)
        p_jekyll.terminate()
        p_browser.terminate()
