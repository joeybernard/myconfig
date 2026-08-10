---
created: 2026-03-24T10:29
updated: 2026-03-24T10:30
---
## Introduction

Every year, when we run the **gen_project_and_allocations.rb** script, some new allocations might not be created under a new RAP. It's quite to automate this logic at the moment so this is a manual procedure to relocate those specific cases to a new RAP.

## Get the list of RPP RAPs to be fixed

In **support_scripts/rac_master_spreadshee**t, run **./gen_project_and_allocations.rb --fix_rpp_raps** to get the list of error cases to work on.

[qnguye@ccdbdev rac_master_spreadsheet]$ ./gen_projects_and_allocations.rb --fix_rpp_raps
***** Fix RPP RAPs *****
LIST OF RAPs THAT HAVE MORE THAN 1 ACTIVE RPP
rpp-julemai [hzw-150-ac], RAP ID: 15829:
        rpp ID: 754
                allocation ID: hzw-150-ac-001, allocation-request ID: 7255
                allocation ID: hzw-150-ac-002, allocation-request ID: 7255
                allocation ID: hzw-150-ac-005, allocation-request ID: 7255
                allocation ID: hzw-150-ac-006, allocation-request ID: 7255
        rpp ID: 866
                allocation ID: hzw-150-ac-003, allocation-request ID: 8067
                allocation ID: hzw-150-ac-004, allocation-request ID: 8067
next available RAP should be: hzw-150-ad
cpp-noskov [udm-233-ag], RAP ID: 14653:
        rpp ID: 679
                allocation ID: udm-233-ag-001, allocation-request ID: 6320
                allocation ID: udm-233-ag-002, allocation-request ID: 6320
                allocation ID: udm-233-ag-004, allocation-request ID: 6320
                allocation ID: udm-233-ag-005, allocation-request ID: 6320
        rpp ID: 952
                allocation ID: udm-233-ag-003, allocation-request ID: 8329
next available RAP should be: udm-233-ah
rpp-ianlewis-ab [fsn-170-ad], RAP ID: 16005:
        rpp ID: 952
                allocation ID: fsn-170-ad-001, allocation-request ID: 8329
        rpp ID: 679
                allocation ID: fsn-170-ad-002, allocation-request ID: 6320
next available RAP should be: fsn-170-ae

## Procedure

### Create a contributed (CTB) RAP under primary role

- Rename ctb to rpp
- Change RAP title to RPP 866 title
- Change RAP description to RPP 866 research summary text

newrap=ResourceAllocationProject.find_by_rapi('hzw-150-ad')
newrap.groupname=’rpp-julemai-ab’
newrap.title=rpp.title
newrap.description=rpp.research_summary_text

newrap.save
newrap.ldap_sync!

If **ldap_sync!** fails:

> **LdapSecondaryGroup.find('rpp-julemai-ab')**
ActiveLdap::EntryNotFound: Couldn't find LdapSecondaryGroup: DN: rpp-julemai-ab: filter: ["cn", "rpp-julemai-ab"]
from /data/ccdb/ccdb-portal/vendor/bundle/ruby/2.6.0/gems/activeldap-6.1.0/lib/active_ldap/operations.rb:367:in `find_one'

> **LdapSecondaryGroup.find_or_new('rpp-julemai-ab', 6080193).update_group(newrap)**
Ignore error Class(No such object): filter (&(cn=rpp-julemai-ab)(&(objectClass=posixGroup)(objectClass=ccAllocation))): attributes: []
=> {:status=>:updated,
:message=>nil,
:account_diff=>
 [["+", "ccRapStatus", "expired"],
  ["+", "ccRapType", "RRG"],
  ["+", "ccRapi", "hzw-150-ad"],
  ["+",
   "ccResource",
   ["hzw-150-ac-003:graham-compute:cpu=7:core_equivalent=21:startdate=2023-04-03",
    "hzw-150-ac-004:graham-storage:project_storage_tb=10:startdate=2023-04-03"]],
  ["+", "ccResponsible", ["hzw-150"]],
  ["+", "description", ["Canadian Surface Prediction Archive CaSPAr"]],
  ["+", "memberUid", ["btolson", "franc", "julemai", "pcouliba", "vfortin"]]]}

[49] pry(main)> **LdapSecondaryGroup.find('rpp-julemai-ab')**
=>
#<LdapSecondaryGroup objectClass:<posixGroup, ccAllocation>,
must:<ccRapStatus, ccRapType, ccRapi, cn, gidNumber, objectClass>,
may:<ccRapMember, ccResource, ccResponsible, description, memberUid, userPassword>,
ccRapMember: [], ccRapStatus: ["expired"], ccRapType:
["RRG"], ccRapi: ["hzw-150-ad"], ccResource:
["hzw-150-ac-003:graham-compute:cpu=7:core_equivalent=21:startdate=2023-04-03",
"hzw-150-ac-004:graham-storage:project_storage_tb=10:startdate=2023-04-03"],
ccResponsible: ["hzw-150"], cn: ["rpp-julemai-ab"],
commonName: ["rpp-julemai-ab"], description: ["Canadian Surface
Prediction Archive CaSPAr"], gidNumber: [6080193], memberUid:
["btolson", "franc", "julemai",
"pcouliba", "vfortin"], objectClass: ["posixGroup",
"ccAllocation"], userPassword: []>

### Make sure the new RAP is the correct type

Check **rap.created_for_allocation_request_id** points to the correct RRG/RPP application.

newrpp=RppApplication.find(866)

newrap=ResourceAllocationProject.find_by_groupname('rpp-julemai-ab')
newrap.created_for_allocation_request_id = newrpp.allocation_request.id
newrap.save!

### Re-associate allocations to new RAP

alloc1=Allocation.find_by_alloc_id('hzw-150-ac-003')
alloc1.rap_id = newrap.id
alloc1.save

alloc2=Allocation.find_by_alloc_id('hzw-150-ac-004')
alloc2.rap_id = newrap.id
alloc2.save

### Rename the alloc_id under the new RAPI

alloc1.alloc_id = 'hzw-150-ad-001'
alloc1.save
alloc2.alloc_id = 'hzw-150-ad-002'
alloc2.save