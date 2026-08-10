---
created: 2026-05-22T15:05
updated: 2026-05-22T18:32
---
## Initial pass at files
Looking at the files under docs/paperclip_pdfs, we see the following make up
- all files - 12483
- files ending in pdf - 9987
	- but not PDF - 97 (4 are empty)
	- of these, it looks like at least some of the files have mime encoding information within the file
- files ending in something else - 2496 (4 are empty)
- empty files - 8
These file lists are in separate files in ~/paperclip

## Initial look at DB
The paperclip table has 12,720 entries. There is a discrepancy with the physical files. When selecting the set of PDF filenames, it also includes an extra term of terminated_at = NULL. This gives 12,455 files. So, still a discrepancy. This means that we have 265 entries with terminated_at=NULL, but no file name set.

Looking at how many entries have terminated_at set to something not null, we get 2281. The total in the table is 15001.

## Databse counts
Looking at a JSON dump of the table, we have the following categorizations of the PDFs
- ResourceApplication
	- applicant_cv - 31
	- justification_doc - 3879
- RppApplication
	- resource_justification_doc - 330
	- loi - 30
	- full_app_doc - 13
	- strategic_plan_doc - 58
- Role
	- rs - 2164
	- cv - 5486
- Cv
	- pc_cv - 551
- MultiPeriodReport
	- other_comments_pdf - 65
	- progress_report - 10


## Notes from Daniel
```
PaperclipPdf stuff:
  PaperclipPdf.pluck(:owner_model).uniq.compact.sort
  PaperclipPdf.pluck(:owner_attribute).inject({}) { |h,v| h[v] = (h[v] || 0) + 1 ; h }
rg '[^a-zA-Z]rs[^u2tary]' app
  PaperclipPdf.where(owner_attribute: 'rs').count
  PaperclipPdf.pluck(:owner_attribute).uniq.map { |a| [a, PaperclipPdf.where(owner_attribute: a).count, PaperclipPdf.where(owner_attribute: a).order(:created_at).last.created_at] }
  PaperclipPdf.where(owner_attribute: 'cv').where('updated_at > ?', Date.parse('2017-01-01')).pluck(:created_at)

Paperclip Cleanup:
  Related: RPP Strategic Plan Cleanup (last one is from 2016)
Migrate Rpp full_app_doc into strategic plan:
  rg strategic_plan
  20250909: OR DO IT THE OTHER WAY AROUND?
    RppApplication.where('strategic_plan_doc_id is not null').pluck(:full_app_doc_id)
  rg full_app_doc
  RppApplication.where('full_app_doc_id is not null').pluck(:created_at)
  RppApplication.where('full_app_doc_id is not null').pluck(:strategic_plan_doc_id)
```

