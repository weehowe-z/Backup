#! /usr/bin/env python

import os
import sys

css_path = "/usr/share/themes/Arc-Dark/gnome-shell/gnome-shell.css"
origin_css = "border-image: url(\"common-assets/panel/panel.svg\") 1 1 1 1; }"
new_css = "background-color: rgba(0,0,0,0.2); }"


def change_top_panel():
    css_file = open(css_path, 'r')
    css_file_new = open(css_path+".new", 'w+')
    try:
        theme_css = css_file.read()
        if (theme_css.find(origin_css) != -1):
            print("find")
            theme_css = theme_css.replace(origin_css, new_css)
            css_file_new.write(theme_css)
        else:
            return
    except Exception as e:
        raise
    finally:
        css_file.close()
        css_file_new.close()
        os.system("cp " + css_path + ".new " + css_path)
        os.system("rm " + css_path + ".new ")


def promote_privileges():
    if os.geteuid():
        args = [sys.executable] + sys.argv
        os.execlp('sudo', 'sudo', *args)


def create_backup():
    print("create backup")
    os.system("cp " + css_path + " " + css_path + ".backup")


def recover_backup():
    print("recover backup")
    os.system("cp " + css_path + ".backup " + css_path)

if __name__ == '__main__':
    promote_privileges()
    # create_backup()
    recover_backup()
    change_top_panel()
