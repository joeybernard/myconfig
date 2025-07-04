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
;;(use-package magit
;;  :ensure t)
;(use-package omnisharp
;  :ensure t)
(use-package tron-legacy-theme
  :config
  :ensure t)

;; org-mode stuff
(setq org-log-done 'time)
(setq org-agenda-files '("~/repos/org-roam" "~/repos/org-roam/daily"))
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

;(use-package org-roam
;  :ensure t
;  :after org
;  :custom
;  (org-roam-directory (file-truename "~/repos/org-roam"))
;  :config
;  (org-roam-setup)
;  (org-roam-db-autosync-mode)
;  (require 'org-roam-dailies)
;  :bind (("C-c n l" . org-roam-buffer-toggle)
;	 ("C-c n f" . org-roam-node-find)
;	 ("C-c n i" . org-roam-node-insert)
;	 ("C-c n I" . org-roam-node-insert-immediate)
;	 ("C-c n p" . my/org-roam-find-project)
;	 ("C-c n t" . my/org-roam-capture-task)
;	 ("C-c n b" . my/org-roam-capture-inbox)
;	 :map org-mode-map
;	 ("C-M-i" . completion-at-point)
;	 :map org-roam-dailies-map
;	 ("Y" . org-roam-dailies-capture-yesterday)
;	 ("T" . org-roam-dailies-capture-tomorrow))
;  :bind-keymap
;  ("C-c n d" . org-roam-dailies-map)
;)

;(defun org-roam-node-insert-immediate (arg &rest args)
;  (interactive "P")
;  (let ((args (push arg args))
;	(org-roam-capture-templates (list (append (car org-roam-capture-templates)
;						  '(:immediate-finish t)))))
;    (apply #'org-roam-node-insert args)))

;(defun my/org-roam-filter-by-tag (tag-name)
;  (lambda (node)
;    (member tag-name (org-roam-node-tags node))))

;(defun my/org-roam-list-notes-by-tag (tag-name)
;  (mapcar #'org-roam-node-file
;          (seq-filter
;           (my/org-roam-filter-by-tag tag-name)
;           (org-roam-node-list))))

;(defun my/org-roam-refresh-agenda-list ()
;  (interactive)
;  (setq org-agenda-files (my/org-roam-list-notes-by-tag "Project")))

;; Build the agenda list the first time for the session
;(my/org-roam-refresh-agenda-list)

;(defun my/org-roam-project-finalize-hook ()
;  "Adds the captured project file to `org-agenda-files' if the
;capture was not aborted."
;  ;; Remove the hook since it was added temporarily
;  (remove-hook 'org-capture-after-finalize-hook #'my/org-roam-project-finalize-hook)

  ;; Add project file to the agenda list if the capture was confirmed
;  (unless org-note-abort
;    (with-current-buffer (org-capture-get :buffer)
;      (add-to-list 'org-agenda-files (buffer-file-name)))))

;(defun my/org-roam-find-project ()
;  (interactive)
;  ;; Add the project file to the agenda after capture is finished
;  (add-hook 'org-capture-after-finalize-hook #'my/org-roam-project-finalize-hook)

  ;; Select a project file to open, creating it if necessary
;  (org-roam-node-find
;   nil
;   nil
;   (my/org-roam-filter-by-tag "Project")
;   :templates
;   '(("p" "project" plain "* Goals\n\n%?\n\n* Tasks\n\n** TODO Add initial tasks\n\n* Dates\n\n"
;      :if-new (file+head "%<%Y%m%d%H%M%S>-${slug}.org" "#+title: ${title}\n#+category: ${title}\n#+filetags: Project")
;      :unnarrowed t))))

;(defun my/org-roam-capture-inbox ()
;  (interactive)
;  (org-roam-capture- :node (org-roam-node-create)
;		     :templates '(("i" "inbox" plain "* %?"
;				  :if-new (file+head "Inbox.org" "#+title: Inbox\n")))))

;(defun my/org-roam-capture-task ()
;  (interactive)
;  ;; Add the project file to the agenda after capture is finished
;  (add-hook 'org-capture-after-finalize-hook #'my/org-roam-project-finalize-hook)

;  ;; Capture the new task, creating the project file if necessary
;  (org-roam-capture- :node (org-roam-node-read
;			    nil
;			    (my/org-roam-filter-by-tag "Project"))
;		     :templates '(("p" "project" plain "** TODO %?"
;				   :if-new (file+head+olp "%<%Y%m%d%H%M%S>-${slug}.org"
;							  "#+title: ${title}\n#+category: ${title}\n#+filetags: Project"
;							  ("Tasks"))))))

;(defun my/org-roam-copy-todo-to-today ()
;  (interactive)
;  (let ((org-refile-keep t) ;; Set this to nil to delete the original!
;	(org-roam-dailies-capture-templates
;	 '(("t" "tasks" entry "%?"
;	    :if-new (file+head+olp "%<%Y-%m-%d>.org" "#+title: %<%Y-%m-%d>\n" ("Tasks")))))
;	(org-after-refile-insert-hook #'save-buffer)
;	today-file
;	pos)
;    (save-window-excursion
;      (org-roam-dailies--capture (current-time) t)
;      (setq today-file (buffer-file-name))
;      (setq pos (point)))

;    ;; Only refile if the target file is different than the current file
;    (unless (equal (file-truename today-file)
;		   (file-truename (buffer-file-name)))
;      (org-refile nil nil (list "Tasks" today-file nil pos)))))

;(add-to-list 'org-after-todo-state-change-hook
;	     (lambda ()
;	       (when (equal org-state "DONE")
;		 (my/org-roam-copy-todo-to-today))))

;(setq org-roam-dailies-capture-templates
;      '(("d" "default" entry "* %<%I:%M %p>: %?"
;	 :if-new (file+head "%<%Y-%m-%d>.org" "#+title: %<%Y-%m-%d>\n"))))

;(use-package org-roam-ui
;  :ensure t
;    :after org-roam ;; or :after org
;;;         normally we'd recommend hooking orui after org-roam, but since org-roam does not have
;;;         a hookable mode anymore, you're advised to pick something yourself
;;;         if you don't care about startup time, use
;  :hook (after-init . org-roam-ui-mode)
;    :config
;    (setq org-roam-ui-sync-theme t
;	  org-roam-ui-follow t
;	  org-roam-ui-update-on-save t
;	  org-roam-ui-open-on-start nil))

(load-theme 'tron-legacy t)


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
 '(package-selected-packages '(use-package tron-legacy-theme))
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


;(setq org-roam-dailies-directory "daily/")

;(setq org-roam-dailies-capture-templates
;      '(("d" "default" entry
;	 "* %?"
;	 :target (file+head "%<%Y-%m-%d>.org"
;			    "#+title: %<%Y-%m-%d>\n"))))
