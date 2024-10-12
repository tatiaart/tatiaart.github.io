from dataclasses import dataclass
import os

excluded_extensions = ["md","sh","py","dir_structure_template.html","zip"]
iconsize = "16px"
import shutil

@dataclass(init=False)
class package:
    title:str
    path:str
    content:str
    
    def __init__(self, title, path:str, content):
        self.title = title
        self.path = path
        self.content = content
        self.parent_dir = "/".join(path.split("/")[:-1])
        
        

class directory:
    def __init__(self, root:str, path:str, dirs:list[str], files:list[str]):
        self.root = root
        self.path = path
        self.basename = path.split("/")[-1]
        self.fullpath = root+path
        self.dirs_names = dirs
        self.files = files
        self.dirs: list[directory] = []
        
    def __str__(self):
        return f"Directory {self.fullpath}:\n{self.dirs}\n{self.files}\n"
    
    def __repr__(self):
        return str(self)


def list_folders(startpath, realpath):
    listf:list[directory] = []
    for root, dirs, files in os.walk(startpath, topdown=False, followlinks=True):
        dirname =  root.replace(startpath, '')
        if(str(dirname).startswith(("/."))):
            continue
        new_dir = directory(realpath, dirname, dirs, files)
        for x in (listf):
            #print(x.path.split("/")[-1], new_dir.dirs_names)
            if(x.basename in new_dir.dirs_names):
                new_dir.dirs.append(x)
        for x in new_dir.dirs:
            if(x in listf):
                listf.remove(x)
        listf.append(new_dir)
    return listf

def format_link(title, url, icon=None,iconsize=None, tooltipstr=None, comment = None, id = None):
    text = ""#f"<div id=\"{title}\" class=\"file_link\">"
    text+=f"<a href = {url} title=\"{(tooltipstr or "")+(title if str(tooltipstr).endswith(" ") else "")}\"{(" id="+"\""+id+"\"")if id else ""}>"
    text+=f"<div id=\"{title}\" class=\"file_link\">"
    if(icon!=None):
        text+=f"<img src = \"/{icon}\" class=\"fileicon\""
        if(iconsize!=None):
            text+=f"width = {iconsize} height = {iconsize}"
        text+=">"
    #text+=f"<a href = {url} title=\"{(tooltipstr or "")+(title if str(tooltipstr).endswith(" ") else "")}\">"
    text+=title
    if(comment!=None):
        text+=f"<span class=\"filesize\">{comment}</span>"     
    text+="</div></a>\n"
    return text


def convert_bytes(num):
    """
    this function will convert bytes to MB.... GB... etc
    """
    for x in ['B ', 'KB', 'MB', 'GB', 'TB']:
        if num < 1024.0:
            return "%3.1f %s" % (num, x)
        num /= 1024.0

def create_index(folder:directory, template_text:str):
    to_write = "\n".join(template_text.splitlines()[:-1])
    in_package = None
    in_package_path = None
    icon = "fold.png"
    for x in packages:
        print(x.path.replace("/_site", ""), "/".join((folder.fullpath.split("/"))))
        if(x.path.replace("/_site", "") in "/".join((folder.fullpath.split("/")))):
            in_package = x.title
            in_package_path = x.path.replace("/_site", "")[1:]
            to_write+=f"\ndownload: {x.path.replace("/_site", "")[1:]}.zip"
            to_write+=f"\ndownloadname: {x.title}"
    if(in_package):
        folder_name = in_package + " / ".join("/".join(folder.fullpath[1:].split("/")).removeprefix(in_package_path).split("/"))
        icon = "package.png"
    else:
        folder_name = "tatiaart.github.io"+" / ".join(folder.fullpath[1:].split("/"))
    if(len(folder.fullpath[1:].split("/"))==1):
        icon = "website.png"
    to_write+="\n---\n"
    to_write+=f"<h2 class = \"foldername\"><img src = \"/{icon}\" class=\"fileicon_big\" height=32px width = 32px>{folder_name}</h2>\n\n"
    if(in_package):
        to_write+= format_link(f"Back to {x.title}", "/".join(folder.fullpath[1:].split("/")[:-1])+".html","foldback.png",iconsize, "Return", "", "returnbutton")
    elif(len(folder.fullpath[1:].split("/"))==1):
        pass
    elif(len(folder.fullpath[1:].split("/"))==2):
        to_write+=format_link("../", "/","foldback.png",iconsize, "Return ", "dir ", "returnbutton")
    else:
        to_write+= format_link("../", "/".join(folder.fullpath[1:].split("/")[:-1])+".html","foldback.png",iconsize, "Return", "dir ", "returnbutton")
    for x in packages:
        if(folder.fullpath.replace(".","./_site") == x.parent_dir):
            in_package = True
            to_write+=format_link(f"{x.title}", f"{x.path.replace("/_site", "")[1:]}.html","package.png",iconsize, "Go to ", f"Packaged Example {convert_bytes(os.stat(f".{x.path[1:]}.zip").st_size).rjust(10)}")
    for x in folder.dirs:
        if(x.fullpath.replace(".","./_site") in [i.path for i  in packages]):
            continue
        to_write+=format_link(f"./{x.basename}", x.fullpath[1:],"fold.png",iconsize, "Go to ", "dir ")
    for x in folder.files:
        if(x.removesuffix(".html") in [y.basename for y in folder.dirs]):
            continue
        if(sum([x.endswith(i) for i in excluded_extensions])>0):
            continue
        to_write+=format_link(x, folder.fullpath[1:]+"/"+x,"html.png" if x.endswith("html") else "file.png",iconsize, "View " if x.endswith("html") else "Download ",
                              (x.split(".")[-1] if len(x.split("."))>1 else "") + " file" +convert_bytes(os.stat(folder.fullpath.replace(".", './_site')+"/"+x).st_size).rjust(10)+"")
        
    fname = folder.fullpath
    if(fname == "."):
        fname = folder.root+"/index"
    with open(f"{fname}.html", "w") as text:
        text.write(to_write)
    for x in folder.dirs:
        create_index(x, template_text)
    
packages = list()
import xml.etree.ElementTree as ET
import tempfile as tf
import pathlib as pl

def add_package(pack: ET.Element):
    new_pkg = package(pack.find("title").text,pack.find("path").text,pack.find("content").text)
    packages.append(new_pkg)
    

def read_packages():
    tree = ET.parse('package_definition.xml')
    root = tree.getroot()
    for child in root:
        add_package(child)
        

def create_package(path, content):
    with open(path.replace("./_site", ".")+".html", "w") as html_file:
        with open("package_redirect_template.html", "r") as template:
            text = template.read()
            text = text.replace("@@@DESTINATION@@@", f"./{path.replace("./_site", ".").split("/")[-1]}/{content.split(".")[0]}")
            html_file.write(text)
    temp_path = tf.mkdtemp()
    shutil.copytree(path, temp_path, dirs_exist_ok=True)
    for root, dirs, files in os.walk(temp_path, topdown=False, followlinks=True):
        for x in files:
            if x.removesuffix(".html") in dirs:
                pl.Path.unlink(root+"/"+x)
    shutil.make_archive(path.replace("./_site", "."), 'zip', temp_path)
    shutil.rmtree(temp_path)
    
    

def main():
    
    read_packages()
    template_text = ""
    with open("./dir_structure_template.html", "r") as text:
        template_text = text.read()
    for x in list_folders("./_site", "."):
        create_index(x, template_text)
        
    for new_pkg in packages:
        create_package(new_pkg.path, new_pkg.content)
    

if __name__ == "__main__":
    main()