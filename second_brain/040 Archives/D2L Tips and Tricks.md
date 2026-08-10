---
tags:
  - D2L
  - Archives
created: 2023-09-06T09:37
updated: 2025-04-09T21:12
---
- The news widgets are independent. If you want news items to go into a particular news widget, you need to go to that news widget. Adding items in the News Tool will make it global to all news widgets.
- Students won't show up until they activate their IT accounts
- Students won't see their courses until the instructor activates it and it is between the start date and end date.
- Any course with NC in the name is non-credit. They manage students in their own system called Destiny. Issues with enrollment should go to customerservice@unb.ca
- In order to unmerge two courses, go the "Manage Section Associations" for the parent course. Delete the association for the relevant child section. This is why we don't delete the old sections when we do a merge. This way, the students have somewhere to go if we have to unmerge.
- To do a bulk load, use something like the following
    cat bulk_load_ids.csv | sed -e "s/^/ENROLL,,/g" | sed -e "s/$/,Student,Undergraduate Student Safety Training-SM2023/g"
- To add guest D2L users, they really need to have guest IT accounts at UNB. We can then create them within D2L and everything will work correctly.
- Regular scheduled outages:
	- 1:30-2:30 - regular backup (may run until 5:00)
	- 6:00-7:00 Wed - regular maintenance window
	- 6:00-9:00 Sun - regular maintenance window
- When trying to test the Student Opinion Survey, we had to not only impersonate a student, but also pretend to do a fresh log in. We can do this by opening the inspect window, click on the Application tab and delete the key "isUserLoggedInD2L". Then any popups, etc, will show up.
- When a student is unenrolled, all of their work goes away. It does get restored if the student is re-enrolled.
- There is a quiz question converter available at https://community.d2l.com/brightspace/kb/articles/4161-quiz-question-converter to take a list of questions and convert them to D2L format.
- In order to change a question type, you can copy a quiz question. You should then be able to set the new question type.
- On lmstest, the insights portal tries to hit the production D2L server. Discovered this by digging into the JavaScript in the page. This is likely why it won't work. We will need to do that part of widget testing on production. Loads of fun.
- If you have a cross-linked course, you can just unenroll the instructor to take it off of their list of courses.