;; Added by Package.el.  This must come before configurations of
;; installed packages.  Don't delete this line.  If you don't want it,
;; just comment it out by adding a semicolon to the start of the line.
;; You may delete these explanatory comments.
;;(package-initialize)
;; disable automatic loading of packages after the init file
;;(setq package-enable-at-startup nil)
;; instead load them explicitly
(package-initialize)
(add-to-list 'package-archives
	     '("melpa" . "https://melpa.org/packages/") t)
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
;(use-package omnisharp
;  :ensure t)
(use-package tron-legacy-theme
  :config
  :ensure t)
;;(use-package org-roam
;;  :ensure t
;;  :after org
;;  :custom
;;    (org-roam-directory (file-truename "~/repos/org-roam"))
;;  :config
;;    (org-roam-setup)
;;    (org-roam-db-autosync-mode)
;;  :bind (("C-c n f" . org-roam-node-find)
;;	 ("C-c n i" . org-roam-node-insert)
;;	 ("C-c n r" . org-roam-node-random)
;;	 (:map org-mode-map
;;	   ("C-c n i" . org-roam-node-insert)
;;	   ("C-c n o" . org-id-get-create)
;;	   ("C-c n t" . org-roam-tag-add)
;;	   ("C-c n a" . org-roam-alias-add)
;;	   ("C-c n l" . org-roam-buffer-toggle))))

;;(use-package org-roam-ui
;;  :ensure t
;;    :after org-roam ;; or :after org
;;         normally we'd recommend hooking orui after org-roam, but since org-roam does not have
;;         a hookable mode anymore, you're advised to pick something yourself
;;         if you don't care about startup time, use
;;  :hook (after-init . org-roam-ui-mode)
;;    :config
;;    (setq org-roam-ui-sync-theme t
;;	  org-roam-ui-follow t
;;	  org-roam-ui-update-on-save t
;;	  org-roam-ui-open-on-start t))

(load-theme 'tron-legacy t)

;; org-mode stuff
(setq org-log-done 'time)
(setq org-agenda-files (list "~/my_org/work.org" "~/my_org/bsc.org"))
(global-set-key (kbd "C-c l") 'org-store-link)
(global-set-key (kbd "C-c a") 'org-agenda)
(global-set-key (kbd "C-c c") 'org-capture)
(setq org-startup-folded nil)
(org-babel-do-load-languages
  'org-babel-load-languages
  '((shell . t)
   )
)
;; keep clock history across sessions
(require 'org-clock)
(setq org-clock-persist t)
(org-clock-persistence-insinuate)


;; Initial setup stuff
(global-visual-line-mode 1)

;; Don't bother allowing the creation of backup files
(setq make-backup-files nil)

(custom-set-variables
 ;; custom-set-variables was added by Custom.
 ;; If you edit it by hand, you could mess it up, so be careful.
 ;; Your init file should contain only one such instance.
 ;; If there is more than one, they won't work right.
 '(column-number-mode t)
 '(display-time-mode t)
 '(indicate-empty-lines t)
 '(package-selected-packages '(use-package tron-legacy-theme omnisharp magit))
 '(show-paren-mode t)
 '(size-indication-mode t)
 '(tool-bar-mode nil))

(setq line-move-visual nil)

(custom-set-faces
 ;; custom-set-faces was added by Custom.
 ;; If you edit it by hand, you could mess it up, so be careful.
 ;; Your init file should contain only one such instance.
 ;; If there is more than one, they won't work right.
 )

;; Cleanup whitespace on save
(add-hook 'before-save-hook 'whitespace-cleanup)

;; Set indent levels for C/C++
(setq c-basic-offset 4)

(add-to-list 'auto-mode-alist '("\\.ipp\\'" . c-mode))

