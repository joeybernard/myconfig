---
created: 2025-12-15T10:36
updated: 2026-04-17T14:58
---

## Step 1 - Open a new round
- the first step is to open a new round for applications
	- edit app/lib/data_extraction.rb and add new entries for the new round this year

## Step 2 - Generate CSV exports
- next step is generating CSV files to populate the master spreadsheet
```sh
cd data_requests/rac

./rac_queries.rb ft  # Fast Track
./rac_queries.rb committee  # proposal by committee
./rac_queries.rb rpp ongoing  # ongoing RPP
./rac_queries.rb rrg  # RRG applications
./rac_queries.rb rpp new  # new RPP
```
- storage comparison - need to edit the year variable to the current year
```sh
./data_requests/rac/storage_comparison_to_previous_year.rb | tee ~/storage_comparison_2026.txt
```

## Step 3 - Import master spreadsheet
- Edit the files support_scripts/rac_master_spreadsheet/import_rac_results
- Run the script
  ```sh
RAILS_ENV=production  ./import_rac_results.rb -v 2>&1| tee ~/import_rac_results_2022_02_10.log
  ```

## Step 4 - Import RAC comments
- Edit the file support_scripts/rac_master_spreadsheet/import_rac_results_comments.rb
- Run the script
```sh
RAILS_ENV=production  ./import_rac_results_comments.rb -v 2>&1| tee ~/import_rac_feedback_2022_02_10.log
```

## Step 5 - Generate Allocations
- Edit the file support_scripts/rac_master_spreadsheet/gen_projects_and_allocations.rb
- Run the script
```sh
RAILS_ENV=production ./gen_projects_and_allocations.rb -v 2>&1 | tee ~/gen_2026_03_24.log
```

## Step 6 - Mailers
- Eduardo gets a copy of every email sent from production. Coordinate with him when doing the sending.
- You can test the RAC mailer by using the '-i' option to select a given application ID.
- For the successful applications, the script has a dry run option
- For the unsuccessful applications, the list of RAS2 and RAS3 cases is hard-coded in the script. Once it is updated, comment one set, run it, then change which group is commented. Then run
```sh
cd support_scripts/rac_allocation_mailer
RAILS_ENV=production ./send_allocation_unsuccessful_notice.rb 2>&1 | tee ~/send_unsuccessful_2026_03_24.log
```
- For the successful cases, you should do a dry run first:
```sh
cd support_scripts/rac_allocation_mailer
RAILS_ENV=production ./send_allocation_notices.rb -v --dry-run --rrg --no-rpp --no-fast-track 2>&1 | tee ~/rrg_notices_2026_03_24.log

RAILS_ENV=production ./send_allocation_notices.rb -v --dry-run --no-rrg --rpp --no-fast-track 2>&1 | tee ~/rpp_notices_2026_03_24.log

RAILS_ENV=production ./send_allocation_notices.rb -v --dry-run --no-rpp --no-rrg --fast-track 2>&1 | tee ~/fast-track_notices_2026_03_24.log
```
- If the dry run is clean, you can run the same scripts again with the flag `--dry-run` removed.

## Step 7 - Generate CSV for allocations
- First go to `support_scripts/rac_master_spreadsheet`
- Then you can run
```sh
RAILS_ENV=production ./gen_projects_and_allocations.rb -r
```
- The output file will be in `/tmp/cc_allocations.csv`

## Step 8 - Check for RPP RAPs to Fix
- Sometimes, we have RPP RAPs that need to be fixed manually. To find them, you go to the directory `support_scripts/rac_master_spreadsheet`.
- Then you can run
```sh
RAILS_ENV=production ./gen_projects_and_allocations.rb -v --fix_rpp_raps 2>&1 | tee ~/fixes_2026_03_24.log
```
- To fix them, you need to follow the directions below

[[Fix RPP RAPs]]


## Extra Steps
### Compare storage from last year to this year
- Go to the directory `data_requests/rac`
- Edit the file `storage_comparison_to_previous_year.rb` to make it work for the current year.
- Run the file with
```sh
RAILS_ENV=production ./storage_comparison_to_previous_year.rb
```
- The output will be in the file `/tmp/rac_2026_vs_2025_storage_comparison_20260324_1051.csv`
- Run a yearly report for Calcul Quebec. Run the script `data_requests/renewals/suzanne_cq_summary.rb`
