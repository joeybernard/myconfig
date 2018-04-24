; This is my overall emacs initialization file

; Load the package management system
(require 'package)
; list the packages you want
(setq package-list '(use-package))
; list the repositories containing them
(setq package-archives '(("melpa" . "https://melpa.org/packages/")
			 ("elpa" . "http://tromey.com/elpa/")
			 ("gnu" . "http://elpa.gnu.org/packages/")
			 ("marmalade" . "http://marmalade-repo.org/packages/")))
; activate all the packages (in particular autoloads)
(package-initialize)
; fetch the list of packages available
(unless package-archive-contents
  (package-refresh-contents))
; install the missing packages
(dolist (package package-list)
  (unless (package-installed-p package)
    (package-install package)))

(require 'use-package)

;; Make sure org mode is loaded
(use-package org
	     :ensure t)


