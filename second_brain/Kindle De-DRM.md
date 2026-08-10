---
created: 2025-02-21T13:19
updated: 2025-02-21T13:20
---
## Old Instructions
Hey all, took me about two hours to actually sift through the conflicting information on Reddit/other websites to work this out, so I thought I'd post it here to help others and as a record for myself in the future if I totally forget again. I am switching from a Kindle to a Kobo e-reader shortly and wanted to have all my kindle books available in my Kobo library once that occured, hence trying to convert them to EPUB format. Here are the steps I took to achieve this:

- Install Calibre (I used the latest version)
    
- Install the following Calibre plugins:
    
    - **KFX Input**, can be found by going to Preferences ⮟ > Get plugins to enhance calibre > Search ‘KFX’.
        
    - **DeDRM Tool**, which needs to be loaded into Calibre separately. I had a few issues with adding it into Calibre so this is the process that finally worked for me*:
        
        - Download the zip file [here](https://github.com/noDRM/DeDRM_tools/releases/tag/v10.0.9).
            
        - Once downloaded, create a new folder and name it whatever you like.
            
        - Extract the zip file into that folder.
            
        - Go to Calibre, then Preferences > Advanced > Plugins > Load plugin from file > New folder you created > Select DeDRM_plugin.zip
            
        - Plugin should successfully load into Calibre.
            
- Install Kindle for PC - Version 2.3.70682
    
    - I used [this](https://www.download3k.com/Install-Kindle-for-PC.html) link - ensure that the ‘70682; is included in the .exe file, otherwise it will download the older version of the Kindle app, but not allow you to download your books as it is an outdated version.
        
- Log into your Kindle account, and download the books you want to convert.
    
- Once downloaded, go to Calibre and select Add Books. Select the books you wish to convert into EPUBs/other formats and they should load onto Calibre.
    
- Once downloaded, select the book(s) and press Convert Books.
    
- When the new menu pops up, ensure the Output Format on the top right is what you require, and press OK.
    
- Voila! It should remove the DRM from your Kindle book.
    

I have just bulk uploaded and converted 251 books via Calibre. I hope this helps someone else!

*I am unsure if this is a neccessary step, but simply extracting to my downloads folder brought up an error whenever I tried to add the plugin to Calibre. When I created a new folder and then extracted into that, it works. ¯\_(ツ)_/¯

## Newer Instructions - as of August 2024
**HERE IS WHAT WORKS AS OF AUGUST 2024** (Windows 10)

Thank you to [u/toobnugget](https://www.reddit.com/user/toobnugget/) for the versions and more instructions, it also worked for me. Here's additional information to help people out. Just do it all in this order.

NOTE: If any of the links are broken, try pasting the broken URL into waybackmachine.org and look for files from today's date (8/12/24) or earlier.

**CONFIRM ALL SOFTWARE IS UNINSTALLED**

1. If you had previous versions of the software installed, uninstall them.
    
2. Then confirm there are no lingering data files with user settings. For example, with kindle, remove these lingering directories if they exist.
    
    C:\Users<USER>\AppData*\Amazon C:\Program Files\Amazon C:\Program Files (x86)\Amazon C:\ProgramData\Amazon
    
3. You can also clear your registry (as described [here](https://www.reddit.com/r/Calibre/comments/1c2ryfz/2024_guide_to_dedrm_kindle_books/m3ddy2a/)) but I would save this as a last resort and only do this if you're unable to get the full instructions from this post to work.
    

**CALIBRE INSTALLATION**

**NOTE**: if you want to use a kindle e-ink device, see step 2 of [u/OccasionallyPrincess](https://www.reddit.com/user/OccasionallyPrincess/)'s comments [here](https://www.reddit.com/r/Calibre/comments/1c2ryfz/2024_guide_to_dedrm_kindle_books/ls6jp9n/) and also [u/SeniorSiesta](https://www.reddit.com/user/SeniorSiesta/)'s comment [here](https://www.reddit.com/r/Calibre/comments/1c2ryfz/2024_guide_to_dedrm_kindle_books/m72dvnp/).

1. Download and install Calibre 7.13 ([download here](https://download.calibre-ebook.com/7.html)) (Some people tested with newer versions (7.2.1) and said it works, but I haven't verified.)
    
2. In Calibre install the KFX input plugin (see OP's instructions up top), restart Calibre
    
3. Download the DeDRM v10.0.9 ([download here](https://github.com/noDRM/DeDRM_tools/releases/tag/v10.0.9), the zip file at the bottom called DeDRM_tools_10.0.9.zip, then extract the zip to a folder.)
    

**NOTE**: Some people had better luck using the alpha version of DeDRM. See [this post here](https://www.reddit.com/r/Calibre/comments/1c2ryfz/2024_guide_to_dedrm_kindle_books/m5uo5uu/?context=3) for more information if v10.0.9 isn't working for you.

1) In Calibre install the DeDRM files (see OP's instructions up top), restart Calibre

**KINDLE INSTALLATION**

**NOTE**: Some people had to **turn off WiFi and unplug ethernet** so they were 100% offline when installing Kindle to avoid automatic updates before disabling it in settings.

**NOTE**: Mac Users, you can probably download newer versions of the kindle app, as confirmed by [this post](https://www.reddit.com/r/Calibre/comments/1c2ryfz/2024_guide_to_dedrm_kindle_books/m4b2u61/).

1) Download and install Kindle 2.4.0(70904)

[https://kindleforpc.s3.amazonaws.com/70904/KindleForPC-installer-2.4.70904.exe](https://kindleforpc.s3.amazonaws.com/70904/KindleForPC-installer-2.4.70904.exe)

See [u/Tilduke](https://www.reddit.com/user/Tilduke/) 's response [here](https://www.reddit.com/r/Calibre/comments/1c2ryfz/2024_guide_to_dedrm_kindle_books/lobl7mh/) for more information.

(Other sites: [download here](https://www.filehorse.com/download-kindle-for-pc/88893/) or [here](https://kindle-for-pc.en.uptodown.com/windows/download/1016990853) or [here](https://www.techspot.com/downloads/4970-kindle-for-pc.html))

6a) Disable your internet

- Many people needed to disable their internet/wifi temporarily for step 6b
    

6b) Launch Kindle (don't login if possible), then go to

- Tools > Options > General > disable "Automatically install updates..."
    
- Tools > Options > Content > define a new path to save the kindle books you download
    
- Finally, re-enable internet and Login (For more information about this step, see [this comment](https://www.reddit.com/r/Calibre/comments/1c2ryfz/2024_guide_to_dedrm_kindle_books/lxnyki9/?context=3))
    

1. Select a book, right click, download
    

**CONFIRM THE DRM IS REMOVED**

1) Find the book you just downloaded from Kindle in the new path (it will be the files that are newest, since they won't have book titles), select the .azw file, and drag it into Calibre. (Do not use the "Add Books" function.)

**NOTE**: Some people had better luck NOT dragging in the file and instead loaded it from the menu. See [this comment](https://www.reddit.com/r/Calibre/comments/1c2ryfz/2024_guide_to_dedrm_kindle_books/m85n106/?context=3) for more information.

1) Once loaded in Calibre, right-click the book > view > view with calibre e-book viewer (if the book opens successfully, then the DRM has been removed. Use pgup and pgdn to see the pages). Close the viewer.

**CONVERTING THE BOOK**

NOTE: This example shows conversion to EPUB, but you can convert to any format you want.

1) In Calibre, right click the book > Convert books > convert individually

2) Choose EPUB on the upper right, then click OK to export

3) If you want to change the location where Calibre exports the book, go to preference (CTRL + P) > click "Run Welcome wizard" at the bottom > then define a new folder for your calibre books to be saved. This folder will be where the book saves when you drag in the .azw file and also where the .epub exports.

For more context, see: [https://www.reddit.com/r/Calibre/comments/1c2ryfz/2024_guide_to_dedrm_kindle_books/lhtah7p/](https://www.reddit.com/r/Calibre/comments/1c2ryfz/2024_guide_to_dedrm_kindle_books/lhtah7p/)