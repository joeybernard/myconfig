
;; Added by Package.el.  This must come before configurations of
;; installed packages.  Don't delete this line.  If you don't want it,
;; just comment it out by adding a semicolon to the start of the line.
;; You may delete these explanatory comments.
;; (package-initialize)
;; disable automatic loading of packages after the init file
(setq package-enable-at-startup nil)
;; instead load them explicitly
(package-initialize)
(add-to-list 'package-archives
             '("melpa-stable" . "https://stable.melpa.org/packages/") t)
;; refresh package descriptions
(unless package-archive-contents
   (package-refresh-contents))

;;; use-package initialization
;;; install use-package if not already done
(if (not (package-installed-p 'use-package))
    (progn
      (package-refresh-contents)
      (package-install 'use-package)))
;; use-package for all others
(require 'use-package)

;; install your packages
;(use-package helm
;  :ensure t)
(use-package magit
  :ensure t)


(custom-set-variables
 ;; custom-set-variables was added by Custom.
 ;; If you edit it by hand, you could mess it up, so be careful.
 ;; Your init file should contain only one such instance.
 ;; If there is more than one, they won't work right.
 '(column-number-mode t)
 '(custom-enabled-themes (quote (misterioso)))
 '(custom-safe-themes
   (quote
    ("8aebf25556399b58091e533e455dd50a6a9cba958cc4ebb0aab175863c25b9a4" default)))
 '(display-time-mode t)
 '(fringe-mode 0 nil (fringe))
 '(indicate-empty-lines t)
 '(org-agenda-files (quote ("~/work.org" "~/bsc.org")))
 '(package-selected-packages (quote (celestial-mode-line)))
 '(show-paren-mode t)
 '(size-indication-mode t)
 '(tool-bar-mode nil))
(custom-set-faces
 ;; custom-set-faces was added by Custom.
 ;; If you edit it by hand, you could mess it up, so be careful.
 ;; Your init file should contain only one such instance.
 ;; If there is more than one, they won't work right.
 )
(if (display-graphic-p)
    (progn
     (setq initial-frame-alist
         '(
           (tool-bar-lines . 0)
           (width . 120) ; chars
           (height . 32) ; lines
           ;(left . 50)
           ;(top . 50)
	   ))
     (setq default-frame-alist
         '(
           (tool-bar-lines . 0)
           (width . 120)
           (height . 32)
           ;(left . 50)
           ;(top . 50)
	   )))
    (progn
     (setq initial-frame-alist '( (tool-bar-lines . 0)))
     (setq default-frame-alist '( (tool-bar-lines . 0)))))

(setq line-move-visual nil)

