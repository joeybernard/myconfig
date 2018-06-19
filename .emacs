; This is my overall emacs initialization file

; Set display properties
(setq inhibit-startup-message t)
(tool-bar-mode -1)
(column-number-mode t)
(display-battery-mode t)
(display-time-mode t)
(size-indication-mode t)

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

; IPython support
(use-package ob-ipython
             :ensure t)
(org-babel-do-load-languages 'org-babel-load-languages
             '((ipython . t)
             ;; other languages..
              ))

(custom-set-variables
 ;; custom-set-variables was added by Custom.
 ;; If you edit it by hand, you could mess it up, so be careful.
 ;; Your init file should contain only one such instance.
 ;; If there is more than one, they won't work right.
 '(package-selected-packages (quote (ob-ipython use-package))))
(custom-set-faces
 ;; custom-set-faces was added by Custom.
 ;; If you edit it by hand, you could mess it up, so be careful.
 ;; Your init file should contain only one such instance.
 ;; If there is more than one, they won't work right.
 )
