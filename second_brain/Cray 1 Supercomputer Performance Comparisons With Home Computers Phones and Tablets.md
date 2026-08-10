---
title: Cray 1 Supercomputer Performance Comparisons With Home Computers Phones and Tablets
source: http://roylongbottom.org.uk/Cray%201%20Supercomputer%20Performance%20Comparisons%20With%20Home%20Computers%20Phones%20and%20Tablets.htm?utm_source=pocket_shared
author: 
published: 
created: 2024-12-09
description: Cray 1 Supercomputer Performance Comparisons With Home Computers Phones and Tablets
tags:
  - clippings
updated: 2024-12-09T13:50
---
###   
Contents

[**Summary and Background Activities**](http://roylongbottom.org.uk/?utm_source=pocket_shared#anchor1)

| [Summary](http://roylongbottom.org.uk/?utm_source=pocket_shared#anchor1a) | [Reliability Studies](http://roylongbottom.org.uk/?utm_source=pocket_shared#anchor1) | [Acceptance Trials](http://roylongbottom.org.uk/?utm_source=pocket_shared#anchor2) |
| --- | --- | --- |
| [System Evaluation and Trials](http://roylongbottom.org.uk/?utm_source=pocket_shared#anchor2a) | [Stress Testing Programs](http://roylongbottom.org.uk/?utm_source=pocket_shared#anchor3) | [Met Seymour Cray](http://roylongbottom.org.uk/?utm_source=pocket_shared#anchor4) |
| [External Consultancy](http://roylongbottom.org.uk/?utm_source=pocket_shared#anchor5) | [Hands on Cray 1](http://roylongbottom.org.uk/?utm_source=pocket_shared#anchor6) | [Collecting Performance Data](http://roylongbottom.org.uk/?utm_source=pocket_shared#anchor7) |
| [Met Key Benchmark Authors](http://roylongbottom.org.uk/?utm_source=pocket_shared#anchor8) | [Influencing Supercomputer Choice](http://roylongbottom.org.uk/?utm_source=pocket_shared#anchor9) | [Benchmarking In Japan](http://roylongbottom.org.uk/?utm_source=pocket_shared#anchor10) |

  
[**My PC Benchmarks**](http://roylongbottom.org.uk/?utm_source=pocket_shared#anchor12)  
[**Detailed Results and Comparisons**](http://roylongbottom.org.uk/?utm_source=pocket_shared#anchor20)

| [Variations](http://roylongbottom.org.uk/?utm_source=pocket_shared#anchor20) | [Cray 1](http://roylongbottom.org.uk/?utm_source=pocket_shared#anchor21) | [Raspberry Pi](http://roylongbottom.org.uk/?utm_source=pocket_shared#anchor22) |
| --- | --- | --- |
| [Android](http://roylongbottom.org.uk/?utm_source=pocket_shared#anchor23) | [Windows PCs](http://roylongbottom.org.uk/?utm_source=pocket_shared#anchor24) | [SIMD Windows and Linux PCs](http://roylongbottom.org.uk/?utm_source=pocket_shared#anchor25) |
| [Vector Whetstone](http://roylongbottom.org.uk/?utm_source=pocket_shared#anchor26) | [MP Whetstone](http://roylongbottom.org.uk/?utm_source=pocket_shared#anchor27) | [MP MFLOPS](http://roylongbottom.org.uk/?utm_source=pocket_shared#anchor27a) |
| [MP MFLOPS Part 2](http://roylongbottom.org.uk/?utm_source=pocket_shared#anchor27b) | [MP Livermore Loops](http://roylongbottom.org.uk/?utm_source=pocket_shared#anchor30a) | [MP MFLOPS 4 to 64 Threads](http://roylongbottom.org.uk/?utm_source=pocket_shared#anchor30) |
| [Performance Summary](http://roylongbottom.org.uk/?utm_source=pocket_shared#anchor27d) | [More Advanced Hardware](http://roylongbottom.org.uk/?utm_source=pocket_shared#anchor27e) | [Disassembled Code](http://roylongbottom.org.uk/?utm_source=pocket_shared#anchor27c) |
| [Benchmark Error Reports](http://roylongbottom.org.uk/?utm_source=pocket_shared#anchor28) | [Run Time Displays](http://roylongbottom.org.uk/?utm_source=pocket_shared#anchor29) | [Faster Than Expected](http://roylongbottom.org.uk/?utm_source=pocket_shared#anchor29a) |

**Also celebrating the 50th anniversary of the Whetstone Benchmark - 1972 to 2022.**

###   
Summary

This report is mainly based on the comprehensive benchmark used to verify performance of the first Cray 1. This comprises the Lawrence Livermore Laboratory program kernels (aka Livermore Loops), that provides a range of Millions of Floating Point Operations Per Second (MFLOPS) measurements. In this case, results from my 1990s conversion to all C code are used.

To support these performance ratings, results are also considered from two similar vintage benchmarks. These are the Linpack and Whetstone benchmarks. The first is linpack-pc.c, my accepted conversion for PCs, available at Netlib. For the second, I took over design responsibility from Harold Curnow, the original author, and developed enhanced variations, including one with 100% vectorisation, the initial target being the first Cray 1 system delivered to the UK.

A selection of available results is provided to demonstrate performance variations and comparisons over the years. Other important issues can be considered, based on the information provided in my first Raspberry Pi report.

"In 1978, the Cray 1 supercomputer cost $7 Million, weighed 10,500 pounds and had a 115 kilowatt power supply. It was, by far, the fastest computer in the world. The Raspberry Pi costs around $70 (CPU board, case, power supply, SD card), weighs a few ounces, uses a 5 watt power supply and is more than 4.5 times faster than the Cray 1"

**Background Activities** - This provides details of my involvement in evaluating, acceptance testing and benchmarking mainframe and supercomputer systems for UK Government and University projects, including hands-on Cray 1 program development of benchmarks and stress tests..

**Results Provided** - Livermore Loops MFLOPS minimum, geometric mean (official average) and maximum, Linpack MFLOPS, Whetstone overall MWIPS and average MFLOPS of appropriate tests. These are all single core benchmarks.

**Raspberry Pi ARM CPUs** - The comment above was for the 2012 Pi 1. In 2020, the Pi 400 average Livermore Loops, Linpack and Whetstone MFLOPS reached **78.8, 49.5 and 95.5 times** faster than the Cray 1.

**Android ARM CPUs** - 2012 Android tablet results identified Cray 1 gains with a range from barely there up to 10 times. My 2021 mid priced phone produced MFLOPS gains of **123, 74 and 151 times**.

**Windows and Linux PCs Intel CPUs** - The first PC to reach the average Cray 1 Livermore Loops score is indicated as a 1994 100 MHz Pentium. Best results for the original benchmarks are for a medium range laptop with a 2021 11th generation 4150 MHz Core i5 CPU. The the three MFLOPS gains were **117, 131 and 134 times**.

**Advanced SIMD** compilations lead to i5 gains of **359, 337 and 226 times**.

**Multiprogramming Livermore Loops** - Four copies of the Advanced SIMD Livermore Loops Benchmark were run at the same time. This resulted in a MFLOPS throughput gain of **1134 times**.

**Vector Whetstones** - This single core benchmark uses large data arrays that produce 100% vectorisation for all test functions and was produced to benchmark the first UK Cray 1. Results are included for thirteen 1978 to 1991 supercomputers. For this benchmark, Single and Double Precision (SP and DP) versions are available, the latter could be appropriate for comparison with supercomputer longer words. Top SP and DP MFLOPS measurements for the **Core i5** were **602 and 433 times** faster than Cray 1.

**Multithreading MP Whetstones** - Results are provided essentially from running multiple copies of the mainly scalar version of the Whetstone benchmark, using 1, 2, 4, and 8 threads, via a single program. It highlights complications due to varying CPU MHz, according to the number of threads, and benefits of PC Hyperthreading. Single and double precision versions were run, in this case obtaining similar performance. Eight thread throughput gains over the Cray 1 were **Raspberry Pi 400 times**, **Android phone 757 times** and **Core i5 laptop 1521 times**.

**MP MFLOPS** - This executes combinations of floating point multiplications and additions handling SP or DP variables, intended to demonstrate near maximum performance, again from a single program. For Intel, assembly code listings are provided for the normally fastest test. Based on the mix of floating point operations, an estimate of Cray 1 maximum speed, running these, is reduced from 160 MFLOPS to 122. The **Core i5 laptop** gains, over the revised Cray 1 maximum rating, were **SP 2671 and DP 1317 times** via **326 and 161 GFLOPS**. Gains on the other devices were **Android phone SP 293 times** and **Raspberry Pi SP 247 times**, both at greater than **30 GFLOPS**. This benchmark has a run time parameter to use up to 64 threads that should demonstrate far superior performance of more advanced CPUs.

[Background Activities Next](http://roylongbottom.org.uk/?utm_source=pocket_shared#anchor1) or [Go To Start](http://roylongbottom.org.uk/?utm_source=pocket_shared#anchorStart)

###   
Background Activities

**Reliability Studies** - I worked for the UK Government Central Computer Agency from 1960, initially analysing fault returns that were contractually required for all new systems. These provided the first detailed statistics included in my book “Computer System Reliability” published in 1980. I also provided assistance in running acceptance tests, gathering similar information, over the years, for inclusion in my book.

**  
Acceptance Trials and First Supercomputer Involvement** - During the late 1960s, with 20 staff, I became in charge of all acceptance trials, taking personal responsibility for top of the range computers. This included organising and supervising trials the UK Atlas 2 for Cambridge University Mathematical Laboratory, the 1962 earlier version said to be the most powerful supercomputer in the world.

**  
Scientific Systems Evaluation and Acceptance Trials** - In the 1970s and early 1980s, with up to 15 staff, I covered evaluating and acceptance testing of scientific systems, with continuing responsibility for design and acceptance trial supervision of the larger systems. Between 1972 and 1973 these included an IBM 360/195 for UK Met Office and a CDC 7600 for ULCC (University of London), again said to be the current fastest supercomputers.

**  
Stress Testing Programs** - In order to stress test all computers, during acceptance tests and under Operating Systems, I produced a range of Fortran programs, a few for testing CPUs, with others covering everything from paper tape punches to disk drives. These had parameters to run for extended periods and were used during hundreds of acceptance tests from 1972 up until the 1990s. The tests included the Whetstone benchmark, produced by my CCTA colleague Harold Curnow and the first accepted general purpose computer benchmark. I collected running times of most programs for use in performance evaluation.

**  
Met Seymour Cray** - It must have been 1969, when I was visiting Control Data manufacturing facility in Minnesota, that I was asked to visit Chippewa Falls in Wisconsin to witness a UK Met Office benchmark run on the CDC 7600. Then, I had a brief encounter with Seymour Cray, who appeared to run the benchmark. After setting it up, it was all over in a flash, with Seymour reported that it took not a lot of milliseconds. This influenced my later development of general purpose benchmarks to have have noticeable running times with ongoing displays of progress.

**  
External Consultancy** - CCTA had contractual responsibility for handling procurement of centrally funded university computers, leading to me becoming an advisor to the Computer Board for Universities and Research Councils, and later a member of the Technical Sub-Group for Advanced Research Computers. In 1976, I was appointed, as an expert from a Member State, to join a European Centre for Medium-Range Weather Forecasts Committee, involving procurement of a new supercomputer, where a Cray 1 became the obvious choice.

**  
Hands-on Cray 1** - My detailed involvement in real supercomputers started in in 1978, including a second visit to Chippewa Falls to evaluate the Cray 1. This was followed by a pre-delivery factory trial, in 1979, for the new AWRE Aldermaston system.. Meanwhile, Cray 1 serial 1 was at the UK Rutherford Laboratory, where I converted all my appropriate test programs, and Whetstone benchmark, to use the new vector instructions. The on-site acceptance trials were carried out later in 1979, where the Cray 1 passed with flying colours. This was followed by the same factory and on-site testing procedures on serial 1 CDC Cyber 205 for UK Met Office, in 1981. That one failed its first factory trial due to my I/O stress testing program identifying a design fault.

**  
Collecting Performance Data** - Next, until my early retirement in 1993, I was mainly involved in performance consultancy of data processing systems, personally covering more than 60 projects. I also took over design responsibility for the Whetstone benchmark and continued consultancy on university procurements. Starting during this period, I collected published details of computers, amounting to more than 2000 mainframes, minicomputers, supercomputers and workstations, from around 120 suppliers. I also continued collecting Whetstone results, ending with more than 700 from 53 computer manufacturers, covering minicomputers, through mainframes, to supercomputers. This lead to the production of reports that included manufacturing dates and versions in PDF format, more appropriate for reference purposes. The majority of reports were uploaded to ResearchGate in this format. these can be viewed by downloading [Computer Benchmarks and Stress Tests and Performance History Index.pdf](https://www.researchgate.net/profile/Roy-Longbottom/publication/367532477_Computer_Benchmarks_and_Stress_Tests_and_Performance_History_Index/links/65ae84639ce29c458b944dff/Computer-Benchmarks-and-Stress-Tests-and-Performance-History-Index.pdf?origin=publicationDetail&_sg%5B0%5D=Qy7974xhw2Xls3gJeanGXI6Q2ewaa9MvIWr9rDrhLzERhADs7c1HJVSITOVE5mRiuGbmRhK0f-gJHLPi0uQY6Q.KShKMlHyxCaF8F3MIN7aTRdVS4_Zdloefhj-HFiiFVtYncUsU_H9MUVb__0kTkpEX6mGR8yngBmIXh-tycKlSA&_sg%5B1%5D=vclXf8JHZ1CsdkAnzmf3PtUtTkNznLL0SjA_fWX0J6r1y6fYXkETJV9NC109qcxkQ-wovFt4UMMsXTRvD9xAaODqzrmpxtZerphUHwcPteZU.KShKMlHyxCaF8F3MIN7aTRdVS4_Zdloefhj-HFiiFVtYncUsU_H9MUVb__0kTkpEX6mGR8yngBmIXh-tycKlSA&_iepl=&_rtd=eyJjb250ZW50SW50ZW50IjoibWFpbkl0ZW0ifQ%3D%3D&_tp=eyJjb250ZXh0Ijp7ImZpcnN0UGFnZSI6InByb2ZpbGUiLCJwYWdlIjoicHVibGljYXRpb24iLCJwb3NpdGlvbiI6InBhZ2VIZWFkZXIifX0), Unfortunately ResearchGate changed the file structure, leaving older compressed files, containing benchmark programs and source code, being no longer available. In this HTM version, access to reports enabling the latter are now from the author’s website or via [the Wayback Archive](http://web.archive.org/web/20240715000000*/roylongbottom.org.uk).

The initial historic reports were [whetstone.htm - Whetstone Benchmark History and Results 1973 to 2014](http://roylongbottom.org.uk/whetstone.htm). and [mips.htm - Computer Speed Claims 1980 to 1996](http://roylongbottom.org.uk/mips.htm) also [cpumix.htm - Computer Speeds From Instruction Mixes pre-1960 to 1971](http://roylongbottom.org.uk/cpumix.htm).

**  
Met Key Supercomputer Benchmark Authors** - As part of a university benchmark investigation team, I visited the USA in 1987, including to the creator of the Linpack range of benchmarks, Jack Dongarra in Tennessee, and to the Lawrence Livermore Research Laboratory, who produced the Livermore Loops (Livermore Fortran Kernels) benchmark. This became the key supercomputer benchmark for a number of years.

**  
Influencing Supercomputer Choice** - In 1988, the Director of University of Manchester Regional Computer Centre requested my performance analysis of the two competing supercomputers, after being quoted by part of the evaluation team that I would support one of the proposals. I demonstrated the opposite choice, that was accepted, using results of my scalar and vector Whetstone benchmark results. This is based on a large number of users, where 90% of programs can be vectorised. Then, the one with the fastest maximum vector speed, but the lowest for scalar code, lost the battle.

**  
Benchmarking Supercomputers in Japan** - My last involvement in supercomputers was for a new one for University of London Computer Centre, over 1991 and 1992, when I became the independent observer of a benchmark, based on numerous real applications, at Fujitsu and NEC in Japan. My colleague dealt with Cray, in the USA, that won the contract with a Y-MP configuration. As confirmed with my simple scalar and vector Whetstone, that I ran then, it was really comparing multiple pipelines against multiple CPUs, each of the latter with scalar and vector processing capabilities.

[My PC Benchmarks Next](http://roylongbottom.org.uk/?utm_source=pocket_shared#anchor12) or [Go To Start](http://roylongbottom.org.uk/?utm_source=pocket_shared#anchorStart)

###   
My PC Benchmarks

**Classic Benchmarks** - Following retirement came part time consultancy and eventually creating my website (roylongbottom.org.uk) to house copies of performance data, collected during my CCTA days (with approval) and a range of benchmarks, initially concentrating on those for PCs, all for free with no adverts. The first, being detailed in my [classic.htm - Classic Computer Benchmarks](http://roylongbottom.org.uk/classic.htm) report, covering Whetstone, Dhrystone, Linpack 100 and Livermore Loops, using C/C++ compiled programs. Early PCs had poor timer resolution, with benchmarks or functions requiring running times of 5 seconds for consistent performance. Other requirements included logging results in text files, checking output for consistent numeric results and, where possible, performance and results displayed as the tests progressed. Besides benchmark reports, identified below, I developed programs in assemly code, with report [whatcpu results.htm - PC CPUID 1994 to 2013, plus Measured Maximum Speeds](http://roylongbottom.org.uk/whatcpu%20results.htm) and [cpuspeed.htm - PC CPU Specifications 1994 to 2014, plus Measured MIPS and MFLOPS per MHz](http://roylongbottom.org.uk/cpuspeed.htm).

**  
Netlib Involvement** - Other than for my Whetstone programs, the initial source code was obtained from Netlib, where my linpack-pc.c code, was later accepted and included, for use on PCs. Livermore Loops conversion was time consuming, where C code was available for the calculations, but data generation, checking and other activities were in Fortran, that I converted to C. All these followed conversion routes from running under DOS, though variations of Windows, Linux, including Raspberry Pi, and Android, most at 32 bits and 64 bits. The majority of early results were collected through involvement in Compuserve Benchmark and Standards Forum.

**  
Livermore Loops** - Results shown here are for the second version of this benchmark, comprising 24 loops. Besides MFLOPS measurements for each of these, summary minimum, maximum and various averages are produced, with geometric mean being the official average. During my visit to LLL, I was given a copy of the 1986 report “The Livermore Fortran Kernels: A Computer Test of the Numerical Performance Range”, with over 200 pages of results for minicomputers to supercomputers. The document appears to be available via Internet, but I never managed to obtain a free download. My report [livermore loops results.htm - Results On PCs and Later Devices up to 2017](http://roylongbottom.org.uk/livermore%20loops%20results.htm). As for the other Classic Benchmarks, later details are included in reports covering the different platforms.

**  
Linpack 100** - Performance of this original version of the benchmark is dependent on a function that simply calculates dy\[i\] = dy\[i\] + da\*dx\[i\]; but with too many overheads that prevent performance from approaching maximum possible. However, this can be compiled to use linked (fused) multiply and add instructions, such as available on the Cray 1 and later computers, particularly with SIMD vector capabilities. As for Livermore Loops, run on systems with smaller word sizes than Cray 1, it is compiled to use double precision arithmetic. Detailed results of this original version, and that for the later HPL variety for modern supercomputers, are available from Netlib in document [Performance of Various Computers Using Standard Linear Equations Software](https://www.netlib.org/benchmark/performance.pdf). My report is [linpack results.htm - Linpack Benchmark Results On PCs and Later Devices](http://roylongbottom.org.uk/linpack%20results.htm).

**  
Whetstone** - The current versions include the changes I made to produce performance ratings of each of the eight test functions, particularly to identify cases where some of the code was not being executed (deliberately by some, in the days of minicomputers). Here, the original overall MWIPS ratings are quoted, along with average MFLOPS for the three tests carrying out straightforward calculations. Two other tests include functions such as SIN and LOG, where changes in maths libraries can significantly affect overall MWIPS. This benchmark is based on simple code sequences used in the 1960s, where performance is more inclined to be proportional to CPU MHz until dramatic changed are made in hardware, like the introduction of additional instructions. My report for this benchmark is [whetstone results.htm - Whetstone Benchmark Detailed Later Results](http://roylongbottom.org.uk/whetstone%20results.htm).

**  
Vector Whetstone** - The vector version, converted for the Cray 1, executes the same functions as the scalar version, but covering a number of sequential memory locations, defined by a vector length parameter. Cray 1 performance achieved maximum performance at vector lengths of 64 words and above, with a sawtooth pattern . I have a previous unpublished C/C++ version that I ran on Raspberry Pi 400 and Windows and Linux based PCs, with results, at vector lengths of 256, being provided below.

**  
MP Whetstone** - None of the other benchmarks, covered here so far, exercise more than one CPU core. This MP benchmark currently executes 1, 2, 4 and 8 copies of the standard code via multithreading in a single program. Some results are included to highlight performance gains over the single CPU in the Cray 1.

**  
MP MFLOPS** - Results for this benchmark have been included for comparison with the maximum MFLOPS possible on the Cray 1. The benchmark executes tests with 2, 8 and 32 floating point operations per data word, covering larger caches and RAM. Default operation uses 8 threads but can be changed, up to 64 threads, with a run time parameter. Description and earlier results are available in [MultiThreading Benchmarks.htm - Windows and Linux](http://roylongbottom.org.uk/MultiThreading%20Benchmarks.htm).

[Detailed Results Next](http://roylongbottom.org.uk/?utm_source=pocket_shared#anchor20) or [Go To Start](http://roylongbottom.org.uk/?utm_source=pocket_shared#anchorStart)

###   
Detailed Results and Comparisons

**Variations** - Results provided below, cover Livermore Loops, Linpack and Whetstone benchmarks. Note that the main Livermore report contains numerous results, covering different compilers and possibly hardware changes. As for the Whetstone benchmark, slow performance of single test functions can severely impact overall ratings. The chosen results represent my choice of typical performance.

**  
Cray 1** - The maximum possible hardware performance was said to be 160 MFLOPS for the 80 MHz Cray 1, comprising linked multiply and add, for two results per clock cycle. The LLL benchmark maximum shown is 82.1 MFLOPS with average 11.9 and minimum 1.2. Then Linpack and Whetstone are 27 and 6 MFLOPS, Linpack benefiting from linked multiply and add.

**  
Raspberry Pi** - In 2013 I ran my benchmarks on the first version of Raspberry Pi. These were essentially the same as those used on PCs, under Linux. The programs included the Livermore Loops benchmark and that lead me including the following in a report.

“In 1978, the Cray 1 supercomputer cost $7 Million, weighed 10,500 pounds and had a 115 kilowatt power supply. It was, by far, the fastest computer in the world. The Raspberry Pi costs around $70 (CPU board, case, power supply, SD card), weighs a few ounces, uses a 5 watt power supply and is more than 4.5 times faster than the Cray 1.” This refers to official average geometric mean results.

In 2019 (aged 84), I was invited to become a voluntary member of Raspberry Pi Foundation’s Alpha Testing Team, which I accepted. This lead to me running my benchmarks and stress tests on new top of the range systems before announcement. The supply of new hardware and software, lead to me producing eight additional reports up to the time that this one was written. For those in HTML format see the website opening page contents list [index.htm](http://roylongbottom.org.uk/).

Results from early reports are included in the benchmark specific performance details identified above. At the time, later reports that include links to download the benchmarks are [Raspberry Pi 400 PC Benchmarks and Stress Tests.htm](http://roylongbottom.org.uk/Raspberry%20Pi%20400%20PC%20%20Benchmarks%20and%20Stress%20Tests.htm) and [Raspberry Pi 32 Bit and 64 Bit Benchmarks and Stress Tests.htm](http://roylongbottom.org.uk/Raspberry%20Pi%2032%20Bit%20and%2064%20Bit%20Benchmarks%20and%20Stress%20Tests.htm).

The following MFLOPS comparisons are in the order of Livermore Loops average.

**Comparison** - The three 700 MHz Pi 1 main measurements (Loops, Linpack and Whetstone) were 55, 42 and 94 MFLOPS, with the four gains over Cray 1 being 8.8 times for MHz and 4.6, 1.6, 15.7 times for MFLOPS.

The 2020 1800 MHz Pi 400 provided 819, 1147 and 498 MFLOPS, with MHz speed gains of 23 times and 69, 42 and 83 times for MFLOPS. With more advanced SIMD options, the 64 bit compilation produced **Cray 1 MFLOPS gains of 78.8, 49.5 and 95.5 times**.

```
                            LLLOOPS MFLOPS    MFLOPS  MWIPS MFLOPS    CPU Device
CPU                  MHz    Max  Gmean    Min Linpack Whets  Whets   Year   Year
Main Columns          V             V             V             V
Cray
Cray 1                80   82.1   11.9    1.2     27   16.2 est  6          1978
XMP1                 118  162.2   17.3    2.1    121   30.3     11          1985

Cray 1 Whets     MFLOPS estimated based on XMP results

Raspberry Pi 32 bit
Pi   CPU
1 1176JZF            700    148     55     17     42    271     94   2001   2012
2    A7              900    248    115     42    120    525    244   2011   2014
3   A53             1200    436    184     56    176    725    324   2012   2016
4   A72             1500   1861    679    180    764   1883    415   2015   2019
400 A72             1800   2262    819    217   1147   2258    498   2015   2020

Raspberry Pi 64 bit
400 A72             1800   3353    938    242   1337   2505    573   2015   2020

Rpi 1/Cray 1         8.8    1.8    4.6   13.8    1.6   16.7   15.7
64 bit/32 bit        1.0    1.5    1.1    1.1    1.2    1.1    1.1
64 bit/Cray 1       22.5   40.8   78.8  201.7   49.5  154.6   95.5

Main Columns          #             #             #             #
  
```

[Android Next](http://roylongbottom.org.uk/?utm_source=pocket_shared#anchor23) or [Go To Start](http://roylongbottom.org.uk/?utm_source=pocket_shared#anchorStart)

###   
Android

In 2012, I converted my benchmarks to run via Android, in native ARM code, requiring Java front end programs. The latest versions identify the hardware, automatically running code for ARM or Intel CPUs, under 32 bit or 64 bit Operating Systems. In the early days I obtained lots of results with similar performance, a sample of these being provided below.

**Comparison** - The first results were for tablets that did not have hardware or software to support fast floating point calculations. The earliest with appropriate facilities, from 2012, used the ARM Cortex-A9 processors, starting with 800 Mhz versions. This is indicated as having the three MFLOPS speeds of 20, 11 and 22, or at 10 times Cray 1 CPU MHz, with gains of 1.7, 0.4 and 3.7 in MFLOPS.

A later 800 MHz V7-A9 obtained 115, 101 and 155 MFLOPS, or Cray 1 gains of 9.7, 3.7 and 25.8 times.

Fastest results provided are for a 2021 mid priced phone with a Kryo 570 CPU, said to be based on ARM Cortex-A77. At 2000 MHz, this obtained an average LLL speed of 1468 MFLOPS, with Linpack at 1986 and 905 for Whetstone and **Cray 1 performance gains of 123, 74 and 151 times**, at 25 times CPU MHz.

The latest versions of the benchmarks can be downloaded and installed from the following (see security warning). [Android 9 benchmarks.htm](http://roylongbottom.org.uk/Android%209%20%20benchmarks.htm). Then [Android 10 and 11 Benchmarks and ARM bigLITTLE Architecture Issues.htm](http://roylongbottom.org.uk/Android%2010%20and%2011%20Benchmarks%20and%20ARM%20bigLITTLE%20Architecture%20Issues.htm) might be of interest, with [android benchmarks.htm](http://roylongbottom.org.uk/android%20benchmarks.htm) providing more information, results and access to older (out of date) apps.

```
                            LLLOOPS MFLOPS    MFLOPS  MWIPS MFLOPS    CPU Device
CPU                  MHz    Max  Gmean    Min Linpack Whets  Whets   Year   Year
Main Columns          V             V             V             V

Cray 1                80   82.1   11.9    1.2     27   16.2    6.0          1978

Android 32 bits
V7-A9 a              800     36     20     11     11    171     22   2012   2012
V7-A9 a later        800    253    115     47    101    687    155   2012   2012
v7-A9               1200    208    176     27    159    731    259   2012   2012
v8-A53              1300    397    164     28    348    868    332   2012   2015
v7-A15              1700    471    342     34    826    907    329   2012   2013
QU-800              2150    447    356    112    630   1974    610   2013   2013
V8-A72              1800    674    584    136   1023   2053    465   2015   2015

Android 64 bits
v8-A53              1300    805    238    101    338   1494    319   2012   2015
Exynos 8890         2300    188    158     27    999   3342    760   2016   2017
v8-A57              2000    724    641    245   1163   1988    390   2013   2015
v8-A73              2000    877    786    269   1122   2927    497   2016   2019
Kryo 570            2000   1620   1468    514   1986   4650    905   2020   2021

A53 64/32bit         1.0    2.0    1.5    3.6    1.0    1.7    1.0
V7-A9 a/Cray 1      10.0    0.4    1.7    9.2    0.4   10.6    3.7
v7-A9 later         10.0    3.1    9.7   39.2    3.7   42.4   25.8
32b A72/Cray 1      22.5    8.2   49.0  113.5   37.9  126.7   77.5
64b 570/Cray 1      25.0   19.7  123.3  428.0   73.6  287.1  150.8

Main Columns         #             #             #             #
  
```

[PCs Next](http://roylongbottom.org.uk/?utm_source=pocket_shared#anchor24) or [Go To Start](http://roylongbottom.org.uk/?utm_source=pocket_shared#anchorStart)

###   
Windows Intel and AMD CPUs

I developed my benchmarks for Intel CPUs in the 1990s, starting with DOS and OS/2. through varieties of Windows and Linux. The compiled benchmarks and source codes are all available for download via my HTM reports. I received numerous results up to 2005. By 2013, my interests became ARM CPUs, with MHz of those from Intel not increasing sufficiently to show real improvements in performance of my single core benchmarks. Then, my 3.9 GHz CPU was close to maximum speed and, in 2021, this appears to have only reached 5.5 GHz, but now with 16 CPU cores. In order to obtain some up to date performance data, I bought a new laptop with a 11th generation Core i5 CPU that runs at a maximum speed of 4.15 GHz.

**Comparison** - Below are samples of results where details for the three benchmarks were available. The first PC to reach the average Cray 1 Livermore Loops score is indicated as a 1994 100 MHz Pentium, shown as 12 MFLOPS, with Linpack and Whetstone at 12 and 16. This gives approximate Cray 1 comparisons of MHz and the three MFLOPS measurements of 1.3, 1.0. 0.44 and 2.6 times.

PCs with faster Pentium processors continued to produce performance proportional to CPU MHz, with improvements appearing with the 1995 Pentium Pro. At 200 MHz the three MFLOPS measurements were 34, 49 and 41 and four comparisons 2.5, 2.9, 1.8 and 6.8 times.

Next came various Pentium II and III models with improvements to these benchmarks mainly proportional to CPU MHz. Then the 2002 Pentium 4 is show to achieve 187 , 382 and 146 MFLOPS, but at 1700 MHz, producing the four Cray \` comparisons of 21, 16, 14 and 24 times, with decreases in MFLOPS per MHz, compared with earlier Pentiums.

With alternative CPU technology, the per MHz ratio improved with a single core of a 1820 MHz 2007 Core 2 processor obtaining 413, 998 and 374 MFLOPS or Cray 1 improvements of 23, 35, 37 and 62 times.

The 2010 Core i7 range produced an improvement in MFLOPS per MHz, with the 3900 MHz 2013 model obtaining 1108, 2684 and 716 MFLOPS and comparisons 49, 93, 99 and 119 times.

The 2021 laptop with a Core i5 1135G7 CPU provided further gains with a higher MFLOPS per MHz rating for Livermore Loops and Linpack but not much with Whetstone. MFLOPS identified were 1387, 3541 and 802, and **Cray 1 comparisons of 117, 131 and 134 times**.

These results are from running optimised versions of the original Windows Classic Benchmarks livecont.exe, linpcont.exe and whetcont.exe, available in downloadable [BenchNT.zip](http://roylongbottom.org.uk/benchnt.zip).

```
                                                                          LLLoops
                                                                            Gmean
                            LLLOOPS MFLOPS    MFLOPS  MWIPS MFLOPS Device  MFLOPS
CPU                  MHz    Max  Gmean    Min Linpack Whets  Whets   Year per MHz
Main Columns          V             V             V             V

Cray 1                80   82.1   11.9    1.2     27   16.2    6.0   1978    0.15

Windows PCs
AMD 80386             40    1.2    0.6    0.2    0.5    5.7    0.8   1991    0.02
80486 DX2             66    4.9    2.7    0.7    2.6     15    3.3   1992    0.04
Pentium               75     24    7.7    1.3    7.6     48     11   1994    0.10
Pentium              100     34     12    2.1     12     66     16   1994    0.12
Pentium              200     66     22    3.8           132     31   1996    0.11
AMD K6               200     68     22    2.7     23    124     26   1997    0.11
Pentium Pro          200    121     34    3.6     49    161     41   1995    0.17
Pentium II           300    177     51    5.5     48    245     61   1997    0.17
AMD K62              500    172     55    6.0     46    309     67   1999    0.11
Pentium III          450    267     77    8.3     62    368     92   1999    0.17
Pentium 4           1700   1043    187     19    382    603    146   2002    0.11
Athlon Tbird        1000   1124    201     23    373    769    161   2000    0.20
Core 2              1830   1650    413     40    998   1557    374   2007    0.23
Core i5             2300   2326    438     35   1065   1813    428   2009    0.19
Athlon 64           2150   2484    447     48    812   1720    355   2005    0.21
Phenom II           3000   3894    644     64   1413   2145    424   2009    0.21
Core i7 930         3066   2751    732     68   1765   2496    576   2010    0.24
Core i7 4820K       3900   5508   1108     88   2680   3114    716   2013    0.28
Core i5 1135G7      4150   7505   1387     92   3541   3293    802   2021    0.33

Pentium/Cray 1       1.3    0.4    1.0    1.8    0.4    4.1    2.6
i5/Cray 1             52     91    117     77    131    203    134
i5/i7                1.1    1.4    1.3    1.1    1.3    1.1    1.1

Main Columns          #             #             #             #

  
```

[SIMD Windows and Linux Next](http://roylongbottom.org.uk/?utm_source=pocket_shared#anchor25) or [Go To Start](http://roylongbottom.org.uk/?utm_source=pocket_shared#anchorStart)

###   
SIMD Windows and Linux PCs

Following are results from running the benchmarks compiled with SSE, AVX and AVX-512 SIMD options. These employ 128, 256 or 512 bit vector registers simultaneous operating on 4, 8 or 16 single precision (SP) and 2, 4 or 8 double precision (DP) numbers, historically stated as producing maximum SP performance of 4, 8 or 16 MFLOPS per MHz and half those for DP. With 100% fused multiply and add (FMA) type operations these maximum expectations would be doubled. FMA was only available on the Core i5 laptop tested here. It should be noted that using fused operation can result in slightly different accuracy in computed results. The benchmarks report these as errors. See [Error Reports](http://roylongbottom.org.uk/?utm_source=pocket_shared#anchor28). Similar variations were encountered, in the past, using different versions of the compilers.

**Windows** benchmarks, used in this area, were lloops64.exe, linpack64.exe and whetsSSE.exe. These and source code files are included in [Windows-Benchmarks.zip](http://roylongbottom.org.uk/Windows-Benchmarks.zip). Compared with the earlier results, performance increased to achieve **Cray 1 MFLOPS gains of 238, 190 and 182 times**. For this area, double precision Whetstone results are also shown to run at the same speed as the single precision version.

I have had difficulties in using the latest C compilers for Windows, but a new bootable flash drive for Ubuntu 20.04 provided the compiler, enabling more advanced options to be used under Linux. The new benchmarks were initially compiled on an older PC as it did not seem possible to boot the latest flash drive on my new Core i5 based laptop. For the latter, I installed WSL (Windows Subsystem for Linux) in order to compile and run the programs.

**Linux** - The first compilations under Linux were slightly faster than those from Windows. Those used here were compiled on the i5 laptop using the latest gcc 9.3.0 compiler, under Ubuntu. Disassembly code was examined to show that SSE, AVX and AVX-512 instructions were being used, as appropriate. This cannot be guaranteed by relying on compile options. These benchmarks can be downloaded in [Linux-Benchmarks.tar.xz](http://roylongbottom.org.uk/Linux-Benchmarks.tar.xz). The first Linux results, using the AVX SIMD instructions, increased the three i5 Cray 1 gains to 300, 259 and 179 times. AVX-512 hardware was only available on the Core i5 CPU, providing the three **MFLOPS gains of 359, 337 and 226 times**.

The table provides MFLOPS per MHz calculations for Livermore Loops average and maximum results. A major surprise is that the latter for SSE and AVX, of 3.56 and 4.77 were higher than recognised maximum double precision ratios, without FMA, of 2.0 and 4.0. This also applied for SSE for the Core i7 at 3.05. The AVX-512 FMA 47692 MFLOPS ratio of 11.49 suggests significant FMA was being used. See also [Faster Than Expected](http://roylongbottom.org.uk/?utm_source=pocket_shared#anchor29a) below.

```
                                                                             DP LLLoops
                                                                            Gmean     Max
                            LLLOOPS MFLOPS    MFLOPS  MWIPS MFLOPS Device  MFLOPS  MFLOPS
CPU                  MHz    Max  Gmean    Min Linpack Whets  Whets   Year per MHz per MHz
Main Columns          V             V             V             V

Cray 1                80   82.1   11.9    1.2     27   16.2    6.0   1978    0.15    1.03

Windows PCs Earlier SSE Compiler
Core i7 4820K       3900   6145   2037    327   3601   6385   1081   2013    0.52    1.58
Core i5 1135G7      4150   8313   2828    386   5132   7466   1094   2021    0.68    2.00
Core i5 DP          4150                               7256   1098
i5/Cray 1             52    101    238    321    190    461    182
i5/i7                1.1    1.4    1.4    1.2    1.4    1.2    1.0

Linux PCs SSE New Compiler
Core i7 4820K       3900  11881   2578    569   5306   6007   1182   2013    0.66    3.05
Core i5 1135G7      4150  14786   3364    575   7322   6586   1052   2021    0.81    3.56
i5/Cray 1             52    180    283    479    271    407    175
i5/i7                1.1    1.2    1.3    1.0    1.4    1.1    0.9

Linux PCs AVX New Compiler
Core i7 4820K       3900  12878   2615    597   5098   5887   1174   2013    0.67    3.30
Core i5 1135G7      4150  19794   3568    943   6998   6477   1077   2021    0.86    4.77
Core i5 DP                                             6861   1076
i5/Cray 1             52    241    300    786    259    400    179
i5/i7                1.1    1.5    1.4    1.6    1.4    1.1    0.9
SP/DP                                                   0.9    1.0
i7 AVX/SSE                  1.1    1.0    1.0    1.0    1.0    1.0
i5 AVX/SSE                  1.3    1.1    1.6    1.0    1.0    1.0

Linux AVX 512 FMA New Cpmpiler
Core i5 1135G7      4150  47692   4273    965   9088   8193   1353   2021    1.03   11.49
i5/Cray 1             52    581    359    805    337    506    226

Main Columns          #             #             #             #
  
```

The following is a summary of the range of results on the 2021 Core i5, to show the impact of compilers that support newer technology. Note that trying to run the AVX-512 variety on earlier CPUs, without this option, results in an program failure report. The No SSE results are from [the earlier table](http://roylongbottom.org.uk/?utm_source=pocket_shared#anchor24).

The i5 CPU MHz is 52 times than that for the Cray 1, compared with over 300 times for Livermore Loops and Linpack benchmarks using AVX-512 functions and more than 200 times for Whetstone. Later are multithreading results for the latter, and for a vector version, to highlight the benefits of using more advanced facilities

```
              MFLOPS               i5/Cray 1     
       LLOOPS Linpack Whets  LLOOPS Linpack Whets

No SSE  1387   3541    802     117    131    134 
SSE     3364   7322   1052     283    271    175 
AVX     3568   6998   1077     300    259    179 
AVX512  4273   9088   1353     359    337    226 
 
```

[Vector Whetstone Benchmark Next](http://roylongbottom.org.uk/?utm_source=pocket_shared#anchor26) or [Go To Start](http://roylongbottom.org.uk/?utm_source=pocket_shared#anchorStart)

###   
Vector Whetstone Benchmark

Below are details of supercomputer Whetstone Scalar and Vector benchmark results included in my [whetstone.htm](http://roylongbottom.org.uk/whetstone.htm) Whetstone Benchmark History and Results report. Details of the vector program version are included [above](http://roylongbottom.org.uk/?utm_source=pocket_shared#anchor17). As far as I remember, all these results are from systems using a single scalar CPU, possibly with more than one vector pipeline. Cray was the first manufacturer to produce systems with multiple scalar CPUs but it is not clear if any of the others followed this line in the timescale considered. From the details here, both Cray Y-MP MHz clock speed and scalar MFLOPS are indicated as around twice as fast as Cray 1, with vector MFLOPS four times faster, the system having two vector units. This benchmark is included in [Linux-Benchmarks.tar.xz](http://roylongbottom.org.uk/Linux-Benchmarks.tar.xz) and [Windows-Benchmarks.zip](http://roylongbottom.org.uk/Windows-Benchmarks.zip).

Best results, from the next table, for Core i5 and Raspberry Pi 400 are provided, to demonstrate their superiority over 1991 supercomputers. On top of this, the former have multiple cores, with the potential of four time higher throughput or raw performance. See [MP Whetstone results](http://roylongbottom.org.uk/?utm_source=pocket_shared#anchor27) and those for [MP MFLOPS](http://roylongbottom.org.uk/?utm_source=pocket_shared#anchor27a).

```
                                                     Vector/        
                         Scalar        Vector        Scalar
                     MHz  MWIPS MFLOPS  MWIPS MFLOPS MFLOPS   DATE

Cray 1                80   16.2    5.9     98     47    8.0   1978
CDC Cyber 205         50   11.9    4.9    161     57   11.7   1981
Cray XMP1            118   30.3   11.0    313    151   13.7   1982
Cray 2/1             244   25.8    N/A    425    N/A          1984
Amdahl VP 500   #    143   21.7    7.5    250    103   13.8   1984
Amdahl VP 1100  #    143   21.7    7.5    374    146   19.5   1984
Amdahl VP 1200  #    143   21.7    7.5    581    264   35.3   1984
IBM 3090-150 VP       54   12.1    4.9     60     17    3.6   1986
(CDC) ETA 10E         95   15.7    6.5    335    124   19.2   1987
Cray YMP1            154   31.0   12.0    449    195   16.3   1987
Fujitsu VP-2400/4    312   71.7   25.4   1828    794   31.3   1991
NEC SX-3/11          345   42.9   17.0   1106    441   25.9   1991
NEC SX-3/12          345   42.9   17.0   1667    753   44.3   1991
                # Fujitsu Systems

Core i5 AVX512 SP   4150   7780   1353  21039  28303   20.9   2021 
Core i5 AVX512 DP   4150   8193   1353  21464  20346   15.0   2021

Pi 400 SP           1800   2505    573   3755   2131    3.7   2020
Pi 400 DP           1800   2684    575   3407   1184    2.1   2020
  
```

The following include all three MFLOPS measurements to identify maximum, as the second test sometimes falls behind. Single and double precision results are provided, where either could be valid, depending on numeric precision requirements.

The fastest Whetstone floating point code is not suitable to benefit much from fused multiply and add operation, with one multiply associated with four additions or subtractions. The maximum Core i5 speed of 75.1 GFLOPS is quite impressive. Average i5 **Cray 1 MFLOPS gains were 602 and 433 times**, for single then double precision calculations. Note that some SP SSE MFLOPS per MHz were again greater than 4.0 and AVX above 8.0 and half these with DP. The Raspberry Pi 400 vector performance was not that good but, as shown above, somewhat faster than the scalar speed.

```
                                                                   Average Maximum Average
                                                            Average MFLOPS  MFLOPS  MFLOPS
                   Mode     MHz  MWIPS MFLOPS MFLOPS MFLOPS MFLOPS Per MHz Per MHz xCray 1
Windows SSE
Phenom II        64b SP    3000   4869   4429   3067    751   1593    0.5     1.5      34
Phenom II        64b DP    3000   4897   2418   1722    751   1290    0.4     0.8      27
Phenom II        32b SP    3000   4624   1798   1584    701   1148    0.4     0.6      24

Core i7 4820K    64b SP    3900   7256  14233  12655    958   2513    0.6     3.6      53
Core i7 4820K    64b DP    3900   7299   7416   7019    953   2261    0.6     1.9      48
Core i7 4820K    32b SP    3900  10494  10362   9748   9468   9846    2.5     2.7     209

Core i5 1135G7   64b SP    4150   8435  23709  21246   1043   2862    0.7     5.7      61
Core i5 1135G7   64b DP    4150   8621  12375  11475   1041   2659    0.6     3.0      57
Core i5 1135G7   32b SP    4150  13387  18221  17254  13739  16162    3.9     4.4     344

Linux
Core i7 4820K    Op3 SP    3900  12012  12896   6248  17131  10136    2.6     4.4     216
Core i7 4820K    AVX SP    3900  11924  20394   7124  23551  12938    3.3     6.0     275
Core i7 4820K    Op3 DP    3900  11383   6259   4601   8711   6099    1.6     2.2     130
Core i7 4820K    AVX DP    3900  11526  10509   5789  11950   8533    2.2     3.1     182

Core i5 1135G7   Op3 SP    4150  20870  21024  10721  28800  17088    4.1     6.9     364
Core i5 1135G7   AVX SP    4150  20294  37170  12353  39126  22487    5.4     9.4     478
Core i5 1135G7   A512 SP   4150  21039  62592  13037  75094  28303    6.8    18.1     602
Core i5 1135G7   Op3 DP    4150  20045  10884   8035  14575  10528    2.5     3.5     224
Core i5 1135G7   AVX DP    4150  20526  19270  10311  20360  15152    3.7     4.9     322
Core i5 1135G7   A512 DP   4150  21464  33188  11504  32907  20346    4.9     8.0     433

Raspberry Pi 400 SP        1800   3755   2413   1683   2506   2131    1.2     1.4      45
Raspberry Pi 400 DP        1800   3407   1216   1151   1186   1184    0.7     0.7      25
  
```

[MP Whetstone Benchmarks Next](http://roylongbottom.org.uk/?utm_source=pocket_shared#anchor27) or [Go To Start](http://roylongbottom.org.uk/?utm_source=pocket_shared#anchorStart)

###   
MP Whetstone Benchmark

Previous results compared Cray 1 performance with single CPU cores on the later systems. Here we consider possible implication of using multiple cores, using this benchmark that effectively represents 1, 2, 4 and 8 users concurrently executing the same application, but using different data. Details shown are overall MWIPS ratings, the three MFLOPS measurements, overall harmonic mean MFLOPS, recorded running times, MFLOPS performance gains over the Cray 1 and MFLOPS per MHz ratios for single core activity. Note nominal running time varies due to rough calibration of the number of passes to use. The benchmark is also included in [Linux-Benchmarks.tar.xz](http://roylongbottom.org.uk/Linux-Benchmarks.tar.xz) and [Windows-Benchmarks.zip](http://roylongbottom.org.uk/Windows-Benchmarks.zip).

**Phenom, Windows 7** - This demonstrates almost perfect speed gains using 1 to 2 and 2 to 4 cores, with no further increase using 8 threads.

**Core i7 Desktop** - This can use 4 cores or 8 independent threads at the same time. This application appeared to demonstrate near best case performance gains using 8 threads.

**Core i5 Laptop** - Performance Monitor indicated that this ran at around 4150 MHz using 1 and 2 threads, but reduced to about 3800 MHz for 4 and 8 threads.

**Windows vs Linux** - Average MFLOPS performance was quite similar, on both the i7 and i5 PCs, at the lower level of optimisation shown here.

**Single vs Double Precision** - Results indicated similar performance, as expected from scalar operation.

**PC Performance Gains** - some of the Core i7 speeds were faster than on the i5. For the latter, eight thread **Cray 1 MFLOPS gains were 1521 times**.

**Android Phone** - The Kryo 570 CPU has out-of-order execution, maybe responsible for the highest MFLOPS per MHz ratio of 0.42. But maximum performance of the big/LITTLE CPU arrangement, of 2 fast and 6 slow cores, lead to 8 core performance being only 5 times faster than than for 1 core. Still, the **Cray 1 gain was 757 times**.

**Raspberry Pi 400** - As might be expected, performance of this quad core system produced the same elapsed time using 1, 2 and 4 threads, and a little bit extra with 8 threads. **Maximum Cray 1 gain was 400 times**.

```
                                                     Average       --- Average MFLOPS ---
System           Threads  MWIPS MFLOPS MFLOPS MFLOPS  MFLOPS  Secs xCray 1   Gain Per MHz

Desktop Win 7       1      4086    817    817    752    794    5.0    132     1.0    0.26
Phenom II           2      8149   1635   1616   1501   1582    5.0    264     2.0
4 core              4     16199   3261   3234   2968   3149    5.1    525     4.0
3000 MHz            8     16602   3428   3461   3056   3304   10.1    551     4.2

Desktop Win 10      1      6169   1236   1236    856   1077    4.5    179     1.0    0.28
Core i7 4820K       2     13106   2601   2604   1910   2322    4.2    387     2.2
4 Core 8 Thread     4     25343   5181   5197   3723   4587    4.5    764     4.3
3900 MHz            8     46579  10310  10263   7403   9104    5.0   1517     8.5

Laptop Win 10       1      7555   1195   1216   1046   1147    4.9    191     1.0    0.28
Core i5 1135G7      2     15048   2385   2424   2083   2287    5.0    381     2.0
4 Core 8 Thread     4     27290   4339   4407   3787   4158    5.6    693     3.6
4150 MHz or less    8     53037   8619   8773   7538   8272    5.9   1379     7.2

Linux
Desktop SP          1      6157   1189   1146    931   1076    4.7    179     1.0    0.28
Core i7 4820K       2     12641   2529   2608   1931   2314    4.6    386     2.1
4 Core 8 Thread     4     25490   5204   5213   3900   4685    4.6    781     4.4
3900 MHz            8     43907  10217  10440   7714   9279    5.7   1547     8.6

Desktop DP          1      6500   1235   1252    972   1138    3.9    190     1.0    0.29
Core i7 4820K       2     13098   2542   2636   1938   2328    3.9    388     2.0
4 Core 8 Thread     4     26298   5105   5273   3906   4676    3.9    779     4.1
3900 MHz            8     44758  10268  10435   7755   9312    5.2   1552     8.2

Laptop SP           1      7640   1140   1199   1015   1113    5.0    185     1.0    0.27
Core i5 1135G7      2     14662   2347   2262   1997   2192    5.4    365     2.0
4 Core 8 Thread     4     26754   4320   4387   3752   4133    6.1    689     3.7
4150 MHz or less    8     46016   7885   8264   6701   7556    7.5   1259     6.8

Laptop SP AVX512    1      8432   1281   1280   1248   1269    5.0    212     1.0    0.31
Core i5 1135G7      2     16728   2542   2548   2471   2520    5.0    420     2.0
4 Core 8 Thread     4     29816   4625   4617   4523   4588    6.0    765     3.6
4150 MHz or less    8     54985   9203   9188   8994   9127    6.6   1521     7.2

Laptop DP AVX512    1      8748   1278   1278   1248   1268    4.9    211     1.0    0.31
Core i5 1135G7      2     17372   2542   2542   2481   2521    5.0    420     2.0
4 Core 8 Thread     4     31459   4622   4622   4514   4585    5.5    764     3.6
4150 MHz or less    8     57024   9187   9210   8985   9126    6.0   1521     7.2

Android Phone       1      4327   1010    984    782    913    4.6    152     1.0    0.42
Kryo 570            2      8782   1850   2126   1604   1836    4.5    306     2.0
2 x 2200 MHz +      4     13969   3189   3373   2641   3034    6.9    506     3.3
6 x 1800 MHz        8     21039   4535   4985   4171   4540    7.9    757     5.0

Raspberry Pi 400    1      2266    644    645    376    520    5.0     87     1.0    0.29
4 x Cortex A72      2      4533   1285   1284    751   1038    5.0    173     2.0
1800 MHz            4      9065   2562   2498   1505   2062    5.0    344     4.0
                    8      9611   3284   3375   1543   2402   10.1    400     4.6 
```

[MP MFLOPS Next](http://roylongbottom.org.uk/?utm_source=pocket_shared#anchor27a) or [Go To Start](http://roylongbottom.org.uk/?utm_source=pocket_shared#anchorStart)

###   
MP MFLOPS Linux - Intel Single Precision Results

The benchmark aims at producing maximum measured performance of floating point operation for comparison with the theoretically possible 160 MFLOPS on Cray 1. Here, a Linux benchmark is used, running SSE and AVX Intel SIMD instructions (in [Linux-Benchmarks.tar.xz](http://roylongbottom.org.uk/Linux-Benchmarks.tar.xz)).

Calculations are carried out of the form x\[i\] = (x\[i\] + a) \* b - (x\[i\] + c) \* d + (x\[i\] + e) \* f with 2, 8 or 32 operations per input data word. In each case, accessing 102400, 1024000 and 10240000 data words, covering caches and RAM. Up to 64 threads can be used, each using a dedicated segment of the data, default being 8 threads. Data is checked for consistent values at the end.

Below are measured MFLOPS using 1, 2, 4 and 8 threads for the Core i7 and i5 computers, executing SSE and AVX instructions, plus AVX-512 on the i5. As for MP Whetstones, performance improvements, from doubling the number of threads (MP Gains), are shown to be non-linear for the Core i5 laptop.

Single core MFLOPS per MHz ratios are also shown. Maximum single precision expectations, without FMA instructions, are 4 for SSE and 8 for AVX and 16 for AVX-512, then 32 for the latter, where FMA is used. Then double precision operation expectations are half these values.

It can be seen that, for both i7 and i5, SSE and AVX MFLOPS/MHz ratios were higher than these. I have been unable to identify the reason for these levels of performance, without FMA type instructions being used. For further information see [Faster Than Expected](http://roylongbottom.org.uk/?utm_source=pocket_shared#anchor29a) below.

AVX-512 MFLOPS per MHz was less than 32, one reason being that all instructions were not of the FMA variety, as shown in code disassemblies, shown [below](http://roylongbottom.org.uk/?utm_source=pocket_shared#anchor27c). These indicate that the highest expected speed achievable by the FMA code is just over 76% of maximum with complete FMA instructions, or 24.4 MFLOPS/MHz, close to that obtained.

The performance adjustment is also shown to produce a likely reduction in Cray 1 maximum speed to 122 MFLOPS, executing these functions. The maximum Core i5 **single precision** speed of **325915 MFLOPS** indicates a **Cray 1 gain of 2671 times**. Maximum **double precision** result, from the next page, was **160641 MFLOPS** with a **gain of 1317 times**.

Also **single precision results** on the next page indicate maximum 8 thread speed on **Raspberry Pi of 30150 MFLOPS** or **Cray 1 gain of 247 times** and **Android phone at 35686 MFLOPS** or **gain of 293 times**, both at Intel SSE SIMD level.

```
Threads      1      2      4      8      1      2      4      8      1      2      4      8
KWDs Ops   SSE    SSE    SSE    SSE    AVX    AVX    AVX    AVX AVX512 AVX512 AVX512 AVX512

       Core i7 3900 MHz MFLOPS 
  102  2 10106  22704  47224  54668  11379  27114  56982  63095    N/A    N/A    N/A    N/A
 1024  2  9801  19227  36849  42389  10542  20127  39567  45256
10240  2  5856   9342  10120   9951   6004   9400  10165   9936

  102  8 24258  48818  91871  97077  36354  82307 169881 184765
 1024  8 24356  49258  91911  96902  34820  67057 130960 161412
10240  8 19421  34454  39855  39777  22340  36088  40372  39578

  102 32 23355  46711  88383  93448  45374  88045 171961 177649
 1024 32 23284  46883  88776  93381  45459  91277 172443 178895
10240 32 23107  46102  85346  92767  43834  86697 152019 157381

Maximum  24356  49258  91911  97077  45459  91277 172443 184765
MP Gains   1.0    2.0    3.8    4.0    1.0    2.0    3.8    4.1
AVX/SSE                                1.9    1.9    1.9    1.9
Max/MHz    6.2                        11.7

       Core i5 MFLOPS
   102 2 24612  48845  46738  80544  29021  30791  86020  93812  37656  74288  72164 121973
  1024 2 21362  42345  43579  79180  21656  44753  44415  93920  23333  46844  58968 122122
 10240 2  7495  12295  13298  14067   7620  11160  13454  14020   9274  13455  13337  13995

   102 8 33271  65364  71105 119460  64946 128515 153955 210177  71895 142743 142554 241880
  1024 8 32614  65504  63763 118933  62120 127095 121959 210157  66304 134081 144756 239841
 10240 8 22467  38871  50079  56166  24963  42384  53438  56122  30345  49693  54170  56226

  102 32 33273  58673  69365 119426  64941 124972 133637 225265  94417 170909 324843 325915
 1024 32 32997  39974  86194 119313  64304 125772 125365 224014  91558 185785 324870 324936
10240 32 32777  64727  82112 116115  61061 114491 127026 200120  77458 140903 182219 222231

Maximum  33273  65504  86194 119460  64946 128515 153955 225265  94417 185785 324870 325915
MP Gains   1.0    2.0    2.6    3.6    1.0    2.0    2.4    3.5    1.0    2.0    3.4    3.5
AVX/SSE                                2.0    2.0    1.8    1.9
a512/AVX                                                           1.5    1.4    2.1    1.4
i5/i7      1.4    1.3    0.9    1.2    1.4    1.4    0.9    1.2
MHz       4150   4150   3600   3600   4150   4150   3600   3600   4150   4150   3600   3600
Max/MHz    8.0                        15.6                        22.8
```

[continued below](http://roylongbottom.org.uk/?utm_source=pocket_shared#anchor27b) or [Go To Start](http://roylongbottom.org.uk/?utm_source=pocket_shared#anchorStart)

###   
MP MFLOPS 2 - Intel DP, Android and Raspberry Pi SP

The first columns in this table, provide Core i7 and Core i5 double precision MP MFLOPS results, using. 1 and 8 threads. Calculations below show that performance at 32 operations per word, and other high performing areas, was effectively at half single precision speed, as expected with SIMD. The lower ratios probably reflect half speed double precision calculations and overheads dealing with 64 bit numbers.

Single precision results are also included for the 2000 MHz Kryo 570 Android phone and 1800 MHz Raspberry Pi 400. For these, SIMD level used is equivalent to Intel SSE. Worse than MP Whetstone, this time the Kryo 570, using 8 threads, was only three times faster than during the single thread test. Then, a CPU monitoring app indicated that six cores were running at 1804 MHz, with two at 768 MHz.

```
           Core i7                     Core i5                                     Phone        RPi
Threads      1      8      1      8      1      8      1      8      1      8     1     8     1     8
 Ops/word  SSE    SSE    AVX    AVX    SSE    SSE    AVX    AVX AVX512 AVX512    SP    SP    SP    SP

   102 2  4921  28537   5290  32337  12437  38391  14606  43320  18872  60955  6977 15998  4015 10169
  1024 2  4820  21214   4772  19551   4978  29821   6351  32157   8120  35674  8034 14536  3865  9622
 10240 2  2949   4923   2946   4950   3604   6562   3683   6728   4442   6514  2984  2442   447   585

   102 8 12233  48924  17683  95178  16500  59285  32504 104046  35958 120212
  1024 8 12074  48679  16145  78149  12762  54904  19300  92706  22226 105465
 10240 8  9929  19774  10969  19845  10941  26897  12157  27045  14806  26544

  102 32 11742  46894  22880  89459  16602  58258  32420 111461  47200 160641 12178 34803  7902 28978
 1024 32 11697  46848  22667  88958  16314  59325  31215 107323  42515 151251 12139 35686  7860 30150
10240 32 11615  46395  21983  78687  16315  57399  30488  99303  38532 105812 12137 34050  7326  8537

Maximum  12233  48924  22880  95178  16602  59325  32504 111461  47200 160641 12178 35686  7902 30150
MP Gain    1.0    4.0    1.0    4.2    1.0    3.6    1.0    3.4    1.0    3.4   1.0   2.9   1.0   3.8
MF/MHZ    3.14          5.87           4.0           7.8          11.4          6.1         4.4

Double/Single Precision
   102 2  0.49   0.52   0.46   0.51   0.51   0.48   0.50   0.46   0.50   0.50
  1024 2  0.49   0.50   0.45   0.43   0.23   0.38   0.29   0.34   0.35   0.29
 10240 2  0.50   0.49   0.49   0.50   0.48   0.47   0.48   0.48   0.48   0.47

   102 8  0.50   0.50   0.49   0.52   0.50   0.50   0.50   0.50   0.50   0.50
  1024 8  0.50   0.50   0.46   0.48   0.39   0.46   0.31   0.44   0.34   0.44
 10240 8  0.51   0.50   0.49   0.50   0.49   0.48   0.49   0.48   0.49   0.47

  102 32  0.50   0.50   0.50   0.50   0.50   0.49   0.50   0.49   0.50   0.49
 1024 32  0.50   0.50   0.50   0.50   0.49   0.50   0.49   0.48   0.46   0.47
10240 32  0.50   0.50   0.50   0.50   0.50   0.49   0.50   0.50   0.50   0.48
  
```

### MP Livermore Loops

Four copies of the Livermore Loops Benchmark were run at the same time on the i5 laptop, with a longer parameter for seconds per loop, each program running for around 15 minutes. Using all cores lead to the usual reduction in CPU MHz, but there may have been more throttling to counteract heating effects. Single thread (Geomean) official average speed was 4273 MFLOPS, compared with a per thread average of 3375 here. However, the total throughput of 13500 MFLOPS indicates an **increase over Cray 1 of 1134 times**.

```
         ---------- AVX-512 DP MFLOPS ----------
 Thread  Maximum Average Geomean Harmean Minimum

    1    33413.3  5809.5  3430.8  2293.0   493.7
    2    35648.5  5576.5  3275.7  2223.1   552.1 
    3    35422.7  5953.9  3449.2  2300.6   505.1
    4    36895.5  5746.0  3344.4  2190.7   459.4
```

### MP MFLOPS 4 to 64 Threads

As indicated earlier, MP MFLOPS benchmark can handle up to 64 threads, with an execution command under LINUX (such as ./MPmflops64AVX512 Threads 64). For correct operation, the specified number must be 1, 2, 4, 8, 16, 32 or 64. Following are results on the i5 between 4 and 64 threds. These show that performance can be significantly improved using additional threads, the reason is due to data being allocated to a faster lower level cache.

```
    4 Byte  Ops/  Repeat          MFLOPS Using Number Of Threads
     Words  Word  Passes       4        8       16       32       64

    102400     2   75000    72164   112210   155132   158133   153968
   1024000     2    7500    58968   108429   119118   117709   122011
  10240000     2     750    13337    13824    17251    60342   116964

    102400     8   75000   142554   210116   253359   270576   275220
   1024000     8    7500   144756   212406   233939   236110   242271
  10240000     8     750    54170    54988    64520   174245   235583

    102400    32   75000   324843   312508   316881   318233   327762
   1024000    32    7500   324870   308995   310405   325996   327897
  10240000    32     750   182219   204563   243408   301543   322605
  
```

[Performance Summary below](http://roylongbottom.org.uk/?utm_source=pocket_shared#anchor27d) or [Go To Start](http://roylongbottom.org.uk/?utm_source=pocket_shared#anchorStart)

###   
Performance Summary

Following is a summary of most results, intended to show best case performance gains, over the Cray 1, for different classes of work. Considering the Core i5 details, the first four are for programs that only use (or are intended to use) a single CPU core. The main one for Cray 1 comparison being Livermore Loops average. Linpack is the only one that provides a single measurement. Whetstones identify relative performance of scalar and vector processing. As for MP benchmarks, vector single and double precision results are provided. The former can be used for comparison with those produced via the long word used by Cray, if the numeric accuracy is acceptable.

The MP benchmark results can be used to represent multiple users running the same program or a single program executing multiple threads, each handling a dedicated segment of shared data. Again for the Core i5, MP Whetstone MFLOPS were similar for double and single precision versions, with little opportunity for vectorisation. The simpler Whetstone calculations demonstrate the benefit of hyperthreading with the 4 core, 8 thread throughput being nearly seven times faster than the standalone run. On the other hand, MP MFLOPS suffered from the i5 running at a lower MHz when four cores were being used, leading to 8 thread performance being less than four times faster than via 1 thread. This benchmark identified the highest Cray 1 performance gains of over 2600 times for single precision calculations, but half of this at double precision.

On cost/performance grounds, the Raspberry Pi 400 was better than the Core i5 laptop, in some of the early cases, but worse on others, then fell far behind on benchmarks that could benefit from compilation using Intel Advanced Vector instructions. Compared with the Cray 1, MP performance gains of up to 400 times were recorded.

Just considering performance of the Android phone, the more advanced ARM CPU used provided some significant gains over the Raspberry Pi, but lost the advantage, due to the big/LITTLE architecture, on running the MP MFLOPS 8 thread test. Still, best Cray 1 performance gain was 757 times through using multiple cores.

```
                             Core i5 AVX-512    Android Phone    Raspberry Pi 400
                     Cray 1           X Cray           X Cray           X Cray

CPU MHz 1 Thread         80     4150      52     2000      25     1800      23
CPU MHz 8 Thread        N/A     3600            <1800             1800 

1. Livermore Loops
MFLOPS Max             82.1    47692     581     1620      20     3353      41
MFLOPS Average         11.9     4273     359     1468     123      938      79

2. Linpack
MFLOPS                   27     9088     337     1986      74     1337      50

3. Whetstone
MFLOPS                    6     1353     226      905     151      573      96

4. Vector Whetstone
MFLOPS DP Average        47    20346     433                      1184      25
MFLOPS DP Maximum              32907                              1216
MFLOPS SP Average              28303     602                      2131      45
MFLOPS SP Maximum              75094                              2506

5. MP Whetstone
MFLOPS DP Average         6     9126    1521
MFLOPS DP Maximum               9210
MFLOPS SP Average               9127    1521     4540     757     2402     400
MFLOPS SP Maximum               9203             4985             3284

6. MP MFLOPS
MFLOPS DP 1 Thread      122    47200     387
MFLOPS DP 8 Thread            160641    1317
MFLOPS SP 1 Thread             94417     774    12178     100     7902      65
MFLOPS SP 8 Thread            325915    2671    35686     293    30150     247
```

### More Advanced Hardware

Here, relative Cray 1 performance calculations, for Android devices and PCs, have been for mid range hardware. It is useful to consider apparent more powerful processors.

**CPU MHz** - In a given processing architecture, performance is usually proportional to CPU MHz. This was clear in earlier times, when Pentium, Celeron and Xeon processors had the same core processor. The above benchmarks were run on a Core i5 with maximum turbo speed of 4150 MHz and an ARM CPU at 2000 MHz. The latest 2022 processors appear to be rated at up to 5500 MHz for PCs and 3000 MHz for ARM based phones. These would affect the single core benchmarks but not excessively.

**Multiple Cores** - At least for the laptop and phone used here, full benefits of multiple cores were not apparent. The laptop switched to a lower MHz and the phone’s 8 core big/LITTLE processor maximum performance became not much better than the 4 core Raspberry Pi. Performance appears to be becoming even more unpredictable. The latest (that I have seen) - Intel 24 threads over 16 cores, 8 at up to 5.1 GHz and 8 to 3.8 GHz.Then ARM that has cores 1 at 3200 MHz, 3 at 2420 MHz and 4 at 1800 MHz.

**More Advanced CPU Options** - Some CPUs in the Core range have two 512-bit fused-multiply add (FMA) units that can, potentially, double SIMD performance of the right sort of application. Judging by the improvement in adopting a higher level of SIMD here and consideration of heating effects, I would not bet on it.

[Disassembled Code Next](http://roylongbottom.org.uk/?utm_source=pocket_shared#anchor27c) or [Go To Start](http://roylongbottom.org.uk/?utm_source=pocket_shared#anchorStart)

###   
Disassembled Code

Disassembled code compiled to use AVX-512 and AVX instructions are listed below. The former includes vector fused multiply and add or subtract instructions. With AVX-512 there are 21 arithmetic vector instructions and the expected 32 with AVX, the latter also applying for SSE code. Minimum instructions for full fused multiply and add type is 16, leading to a (16/21) 76.19% reduction in achievable speed. This would lead the maximum Cray 1 MFLOPS for this code becoming 122, instead of 160.

```
 
 AVX-512                                     AVX  
 L22:                                        L60:
    vmovupd (%rax), %zmm0                       vmovups (%rax), %xmm1
    addq    $64, %rax                           vinsertf128     $0x1, 16(%rax), %ymm1, %ymm1
    vaddpd  %zmm0, %zmm28, %zmm31               addq    $32, %rax
    vaddpd  %zmm0, %zmm30, %zmm1                vaddps  -24(%rsp), %ymm1, %ymm0
    vmulpd  %zmm27, %zmm31, %zmm31              vmulps  8(%rsp), %ymm0, %ymm15
    vfmsub132pd     %zmm29, %zmm31, %zmm        vaddps  40(%rsp), %ymm1, %ymm0
    vaddpd  %zmm0, %zmm26, %zmm31               vmulps  72(%rsp), %ymm0, %ymm0
    vfmadd231pd     %zmm31, %zmm25, %zmm        vsubps  %ymm0, %ymm15, %ymm0
    vaddpd  %zmm24, %zmm0, %zmm31               vaddps  104(%rsp), %ymm1, %ymm15
    vfnmadd132pd    %zmm23, %zmm1, %zmm3        vmulps  136(%rsp), %ymm15, %ymm15
    vaddpd  %zmm22, %zmm0, %zmm1                vaddps  %ymm15, %ymm0, %ymm0
    vfmadd231pd     %zmm21, %zmm1, %zmm3        vaddps  168(%rsp), %ymm1, %ymm15
    vaddpd  %zmm20, %zmm0, %zmm1                vmulps  -56(%rsp), %ymm15, %ymm15
    vfnmadd132pd    %zmm19, %zmm31, %zmm        vsubps  %ymm15, %ymm0, %ymm0
    vaddpd  %zmm18, %zmm0, %zmm31               vaddps  %ymm14, %ymm1, %ymm15
    vfmadd231pd     %zmm17, %zmm31, %zmm        vmulps  -88(%rsp), %ymm15, %ymm15
    vaddpd  %zmm16, %zmm0, %zmm31               vaddps  %ymm15, %ymm0, %ymm0
    vfnmadd132pd    %zmm15, %zmm1, %zmm3        vaddps  %ymm13, %ymm1, %ymm15
    vaddpd  %zmm14, %zmm0, %zmm1                vmulps  %ymm12, %ymm15, %ymm15
    vfmadd231pd     %zmm13, %zmm1, %zmm3        vsubps  %ymm15, %ymm0, %ymm0
    vaddpd  %zmm12, %zmm0, %zmm1                vaddps  %ymm11, %ymm1, %ymm15
    vaddpd  %zmm10, %zmm0, %zmm0                vmulps  %ymm10, %ymm15, %ymm15
    vfnmadd132pd    %zmm11, %zmm31, %zmm        vaddps  %ymm15, %ymm0, %ymm0
    vfmadd132pd     %zmm9, %zmm1, %zmm0         vaddps  %ymm9, %ymm1, %ymm15
    vmovupd %zmm0, -64(%rax)                    vmulps  %ymm8, %ymm15, %ymm15
    cmpq    %rax, %rcx                          vsubps  %ymm15, %ymm0, %ymm0
    jne     .L22                                vaddps  %ymm7, %ymm1, %ymm15
                                                vmulps  %ymm6, %ymm15, %ymm15
                                                vaddps  %ymm15, %ymm0, %ymm0
                                                vaddps  %ymm5, %ymm1, %ymm15
                                                vaddps  %ymm3, %ymm1, %ymm1
                                                vmulps  %ymm4, %ymm15, %ymm15
                                                vsubps  %ymm15, %ymm0, %ymm0
                                                vmulps  %ymm2, %ymm1, %ymm15
                                                vaddps  %ymm15, %ymm0, %ymm0
                                                vmovups %xmm0, -32(%rax)
                                                vextractf128    $0x1, %ymm0, -16(%rax)
                                                cmpq    %rdx, %rax
                                                jne     .L60

  
```

[Benchmark Error Reports Next](http://roylongbottom.org.uk/?utm_source=pocket_shared#anchor28) or [Go To Start](http://roylongbottom.org.uk/?utm_source=pocket_shared#anchorStart)

###   
Benchmark Error Reports

**Livermore Loops** benchmark displays details of results for each of the three times 24 sets of calculations. These include the final numeric results, whose values are included in the program and can vary slightly, depending on the hardware and compiler options. The values under OK indicate accuracy in terms of the number of decimal places, double precision numbers being said to be accurate up to 16 decimal places, but possibly subject to rounding errors.

As indicated, there were differences in numeric results from the Core i5 laptop, with accuracy reducing from 15 or 16 decimal places to 12 or 13, using the AVX512 compile option. Apparently, there is only one rounding for fused operations, as opposed to one for each separate instruction.

```
Kernel       Floating Pt ops
No  Passes E No    Total      Secs.  MFLOPS Span     Checksums          OK

Earlier Compilation
 6   3 x 658  2  1.566566e+09  0.89 1751.62   64  4.375116344729986e+03 16
 7   4 x 529 16  6.737344e+09  0.89 7529.02  995  6.104251075174761e+04 16
18   2 x 703 44  6.124536e+09  0.89 6867.09  100  1.015727037502299e+05 15
Log Program report - Numeric results were as expected

AVX Compilation
 6   3 x 814  2  1.937971e+09  1.00 1929.85   64  4.375116344729986e+03 16
 7   4 x 616 16  7.845376e+09  1.00 7835.67  995  6.104251075174761e+04 16
18   2 x1711 44  1.490623e+10  1.0014869.06  100  1.015727037502299e+05 15
Log Program report - Numeric results were as expected

AVX512 Compilation
 6   3 x 757  2  1.802266e+09  1.00 1802.82   64  4.375116344743195e+03 12
 7   4 x3738 16  4.760717e+10  1.0047691.47  995  6.104251075174966e+04 13
18   2 x2393 44  2.084782e+10  1.0020781.51  100  1.015727037502806e+05 12
Log Program report - Examples of different numeric results 

 Test  6 result was  4.375116344743195e+03 expected  4.375116344729986e+03
 Test  7 result was  6.104251075174966e+04 expected  6.104251075174761e+04
 Test 18 result was  1.015727037502806e+05 expected  1.015727037502299e+05
  
```

### MP Linpack and Whetstone Benchmarks Error Reports

Similar sumcheck variations were recorded on running the Linpack and Whetstone benchmarks on the Core i5 based laptop. In both cases, as for the Livermore Loops example, the errors were not reported running on older hardware or from alternative compilations.

```
 Linpack AVX-512
 Linpack Double Precision Unrolled Benchmark n @ 100
 Optimisation AVX512 64 Bit, Tue Dec  7 11:38:24 2021

 Speed    5151.83 MFLOPS

 Variable norm. resid Non-standard result was              1.9 instead of              1.7
 Variable resid       Non-standard result was   8.46778499e-14 instead of   7.41628980e-14
 Variable x[0]-1      Non-standard result was  -1.11799459e-13 instead of  -1.49880108e-14
 Variable x[n-1]-1    Non-standard result was  -9.60342916e-14 instead of  -1.89848137e-14

 Whetstone SSE
 Whetstone Double Precision SSE2 Benchmark Tue Jan 11 19:34:50 2022

 Test 5 Non-standard result was      0.49902937281518372 instead of      0.49902937281518167

  Log file result
   Loop content                  Result              MFLOPS      MOPS   Seconds

  N5 sin,cos etc.         0.49902937281518372                 281.276     2.089
  
```

[Run Time Displays Next](http://roylongbottom.org.uk/?utm_source=pocket_shared#anchor29) or [Go To Start](http://roylongbottom.org.uk/?utm_source=pocket_shared#anchorStart)

###   
Run Time Displays

The running times of benchmarks, used here, are calibrated to run for a given noticeable time, with Windows and Linux versions displaying details on completion of individual test functions. This automatic adjustment has currently survived more than 100 times increase in CPU MHz. The aim for Livermore Loops is currently 1 second for each of the 72 tests, with Linpack 1 second for each of the 10 calculations and Whetstone 10 seconds overall.

```
L.L.N.L. 'C' KERNELS: MFLOPS   P.C.  VERSION 4.0

Calculating outer loop overhead
      1000 times   0.00 seconds
     10000 times   0.00 seconds
    100000 times   0.00 seconds
   1000000 times   0.01 seconds
  10000000 times   0.04 seconds
  20000000 times   0.08 seconds
  40000000 times   0.16 seconds
  80000000 times   0.31 seconds
Overhead for each loop   3.9288e-09 seconds

Calibrating part 1 of 3

Loop count          4  0.00 seconds
Loop count         16  0.00 seconds
Loop count         64  0.00 seconds
Loop count        256  0.01 seconds

Loops  200 x  1 x Passes

Kernel       Floating Pt ops
No  Passes E No    Total      Secs.  MFLOPS Span     Checksums          OK
------------ -- ------------- ----- ------- ---- ---------------------- --
 1   7 x1566  5  1.097296e+10  0.9811171.25 1001  5.114652693224671e+04 16
 2  67 x 595  4  3.093524e+09  0.98 3164.40  101  1.539721811668385e+03 15
 3   9 x 657  2  2.367565e+09  0.95 2494.82 1001  1.000742883066363e+01 15
 4  14 x 728  2  2.446080e+09  0.96 2555.68 1001  5.999250595473891e-01 16
 5  10 x 234  2  9.360000e+08  0.95  980.20 1001  4.548871642387267e+03 16
 6   3 x 904  2  2.152243e+09  0.95 2276.20   64  4.375116344729986e+03 16
 7   4 x 975 16  1.241760e+10  1.0312101.10  995  6.104251075174761e+04 16
 8  10 x 385 36  5.488560e+09  0.95 5788.45  100  1.501268005625795e+05 15
 9  36 x 536 17  6.626246e+09  0.96 6926.99  101  1.189443609974981e+05 16
10  34 x 456  9  2.818627e+09  0.95 2973.11  101  7.310369784325296e+04 16
11  11 x 565  1  1.243000e+09  0.95 1309.65 1001  3.342910972650109e+07 16
12  12 x1201  1  2.882400e+09  0.95 3030.87 1000  2.907141294167248e-05 16
13  36 x 177  7  5.709312e+08  0.95  600.71   64  1.202533961842805e+11 15
14   2 x 290 11  1.277276e+09  0.95 1347.14 1001  3.165553044000335e+09 15
15   1 x 660 33  2.178000e+09  0.96 2268.96  101  3.943816690352044e+04 15
16  25 x 768 10  2.035200e+09  0.94 2153.77   75  5.650760000000000e+05 16
17  35 x 368  9  2.341584e+09  0.96 2447.92  101  1.114641772902486e+03 16
18   2 x 733 44  6.385896e+09  0.97 6567.18  100  1.015727037502299e+05 15
19  39 x 215  6  1.016262e+09  0.95 1070.62  101  5.421816960147207e+02 16
20   1 x 187 26  9.724000e+08  0.95 1021.36 1000  3.040644339351239e+07 16
21   1 x 302  2  7.625500e+09  0.95 8021.31  101  1.597308280710199e+08 15
22  11 x 356 17  1.344754e+09  0.95 1416.60  101  2.938604376566697e+02 16
23   8 x 223 11  1.942776e+09  0.95 2045.20  100  3.549900501563623e+04 16
24   5 x1553  1  1.553000e+09  0.95 1637.44 1001  5.000000000000000e+02 16

                     Maximum   Rate12101.10 
                     Average   Rate 3557.12 
                     Geometric Mean 2580.73 
                     Harmonic  Mean 1966.74 
                     Minimum   Rate  600.71 

                     Do Span    471

Calibrating part 2 of 3

Loop count          8  0.00 seconds
Loop count         32  0.00 seconds
Loop count        128  0.00 seconds

Loops  200 x  2 x Passes

Kernel       Floating Pt ops
No  Passes E No    Total      Secs.  MFLOPS Span     Checksums          OK
------------ -- ------------- ----- ------- ---- ---------------------- --
 1  40 x1061  5  8.572880e+09  0.98 8769.29  101  5.253344778937972e+02 16
 2  40 x 495  4  3.072960e+09  1.01 3046.39  101  1.539721811668385e+03 15
 3  53 x 595  2  2.548028e+09  1.00 2536.39  101  1.009741436578952e+00 16
 4  70 x 949  2  3.188640e+09  1.00 3194.69  101  5.999250595473891e-01 16
 5  55 x 247  2  1.086800e+09  1.00 1082.99  101  4.589031939600982e+01 16
 6   7 x 760  2  2.042880e+09  0.98 2081.44   32  8.631675645333210e+01 16
 7  22 x 858 16  1.220145e+10  0.9912378.97  101  6.345586315784055e+02 16

 More Below or Go To Start 
 

 8   6 x 338 36  5.782234e+09  1.00 5784.83  100  1.501268005625795e+05 15
 9  21 x 483 17  6.966212e+09  1.00 6934.93  101  1.189443609974981e+05 16
10  19 x 431  9  2.977520e+09  1.01 2952.22  101  7.310369784325296e+04 16
11  64 x 536  1  1.372160e+09  1.00 1366.60  101  3.433560407475758e+04 16
12  68 x 931  1  2.532320e+09  1.04 2443.43  100  7.127569130821465e-06 16
13  41 x 165  7  6.061440e+08  1.00  603.71   32  9.816387810944356e+10 15
14  10 x 373 11  1.657612e+09  1.01 1640.50  101  3.039983465145392e+07 15
15   1 x 348 33  2.296800e+09  1.00 2295.02  101  3.943816690352044e+04 15
16  27 x 748 10  2.261952e+09  1.01 2241.47   40  6.480410000000000e+05 16
17  20 x 340  9  2.472480e+09  1.01 2441.10  101  1.114641772902486e+03 16
18   1 x 753 44  6.560136e+09  0.99 6608.43  100  1.015727037502299e+05 15
19  23 x 192  6  1.070438e+09  1.02 1053.29  101  5.421816960147207e+02 16
20   8 x 125 26  1.040000e+09  1.01 1031.93  100  3.126205178815431e+04 16
21   1 x 324  2  8.100000e+09  1.00 8099.88   50  7.824524877232093e+07 16
22   7 x 295 17  1.418242e+09  1.00 1415.93  101  2.938604376566697e+02 16
23   5 x 188 11  2.047320e+09  1.00 2044.93  100  3.549900501563623e+04 16
24  31 x 881  1  1.092440e+09  1.00 1087.94  101  5.000000000000000e+01 16

                     Maximum   Rate12378.97 
                     Average   Rate 3464.01 
                     Geometric Mean 2544.88 
                     Harmonic  Mean 1951.83 
                     Minimum   Rate  603.71 

                     Do Span     90

Calibrating part 3 of 3

Loop count         32  0.00 seconds
Loop count        128  0.00 seconds
Loop count        512  0.00 seconds
Loop count       2048  0.01 seconds

Loops  200 x  8 x Passes

Kernel       Floating Pt ops
No  Passes E No    Total      Secs.  MFLOPS Span     Checksums          OK
------------ -- ------------- ----- ------- ---- ---------------------- --
 1  28 x1795  5  1.085616e+10  1.0010866.23   27  3.855104502494961e+01 16
 2  46 x 748  4  2.422323e+09  1.00 2415.89   15  3.953296986903059e+01 16
 3  37 x1126  2  3.599597e+09  1.01 3575.44   27  2.699309089320672e-01 16
 4  38 x1471  2  2.683104e+09  1.00 2685.18   27  5.999250595473891e-01 16
 5  40 x 473  2  1.574144e+09  1.02 1546.96   27  3.182615248447483e+00 16
 6  21 x1047  2  1.688602e+09  1.01 1665.66    8  1.120309393467088e+00 15
 7  20 x1082 16  1.163366e+10  0.9412311.54   21  2.845720217644024e+01 16
 8   9 x 427 36  5.755277e+09  1.00 5741.74   14  2.960543667875005e+03 15
 9  26 x 664 17  7.043712e+09  1.00 7015.77   15  2.623968460874250e+03 16
10  25 x 557  9  3.007800e+09  1.02 2959.56   15  1.651291227698265e+03 16
11  46 x1015  1  1.942304e+09  1.02 1901.09   27  6.551161335845770e+02 16
12  48 x1714  1  3.422515e+09  1.02 3359.57   26  1.943435981130448e-06 16
13  31 x 226  7  6.277376e+08  1.01  621.29    8  3.847124199949431e+10 15
14   8 x 490 11  1.862784e+09  1.01 1853.19   27  2.923540598672009e+06 15
15   1 x 639 33  2.361744e+09  1.00 2361.30   15  1.108997288134785e+03 16
16  14 x 974 10  2.399936e+09  1.00 2394.06   15  5.152160000000000e+05 16
17  26 x 513  9  2.881008e+09  1.00 2875.92   15  2.947368618589361e+01 16
18   2 x 647 44  5.921344e+09  1.00 5907.72   14  9.700646212337041e+02 16
19  28 x 273  6  1.100736e+09  1.02 1074.17   15  1.268230698051003e+01 15
20   7 x 145 26  1.097824e+09  1.02 1077.78   26  5.987713249475302e+02 16
21   1 x 212  2  8.480000e+09  1.01 8435.26   20  5.009945671204667e+07 16
22   8 x 421 17  1.374144e+09  1.00 1373.68   15  6.109968728263972e+00 16
23   7 x 356 11  2.850848e+09  1.00 2862.02   14  4.850340602749970e+02 16
24  23 x 952  1  9.108736e+08  1.00  910.11   27  1.300000000000000e+01 16

                     Maximum   Rate12311.54 
                     Average   Rate 3657.96 
                     Geometric Mean 2704.87 
                     Harmonic  Mean 2064.49 
                     Minimum   Rate  621.29 

                     Do Span     19

                Overall

                Part 1 weight 1
                Part 2 weight 2
                Part 3 weight 1

                     Maximum   Rate12378.97 
                     Average   Rate 3535.78 
                     Geometric Mean 2593.02 
                     Harmonic  Mean 1982.64 
                     Minimum   Rate  600.71 

                     Do Span    167
  More Below or Go To Start 
 

Unrolled Double Precision Linpack Benchmark - PC Version in 'C/C++'

Optimisation AVX 64 Bit

norm resid      resid           machep         x[0]-1          x[n-1]-1
   1.7    7.41628980e-14   2.22044605e-16  -1.49880108e-14  -1.89848137e-14

Times are reported for matrices of order          100
1 pass times for array with leading dimension of  201

      dgefa      dgesl      total     Mflops       unit      ratio
    0.00016    0.00001    0.00017    4091.04     0.0005     0.0030

Calculating matgen overhead
        10 times   0.00 seconds
       100 times   0.00 seconds
      1000 times   0.03 seconds
     10000 times   0.28 seconds
     20000 times   0.54 seconds
     40000 times   1.02 seconds
Overhead for 1 matgen      0.00003 seconds

Calculating matgen/dgefa passes for 1 seconds
        10 times   0.00 seconds
       100 times   0.02 seconds
      1000 times   0.17 seconds
      2000 times   0.32 seconds
      4000 times   0.64 seconds
      8000 times   1.27 seconds
Passes used       6311 

Times for array with leading dimension of 201

      dgefa      dgesl      total     Mflops       unit      ratio
    0.00013    0.00000    0.00014    5049.22     0.0004     0.0024
    0.00013    0.00000    0.00014    4949.89     0.0004     0.0025
    0.00013    0.00000    0.00014    4956.75     0.0004     0.0025
    0.00013    0.00000    0.00014    5048.17     0.0004     0.0024
    0.00013    0.00000    0.00014    5049.18     0.0004     0.0024
Average                              5010.64

Calculating matgen2 overhead
Overhead for 1 matgen      0.00003 seconds

Times for array with leading dimension of 200

      dgefa      dgesl      total     Mflops       unit      ratio
    0.00012    0.00000    0.00013    5372.95     0.0004     0.0023
    0.00012    0.00000    0.00013    5374.23     0.0004     0.0023
    0.00012    0.00000    0.00013    5370.76     0.0004     0.0023
    0.00012    0.00000    0.00013    5462.18     0.0004     0.0022
    0.00012    0.00000    0.00013    5463.74     0.0004     0.0022
Average                              5408.77

Unrolled Double  Precision     5010.64 Mflops 

Single Precision C Whetstone Benchmark AVX 64 Bit, Tue Jan 18 23:29:03 2022

Calibrate
       0.01 Seconds          1   Passes (x 100)
       0.01 Seconds          5   Passes (x 100)
       0.05 Seconds         25   Passes (x 100)
       0.23 Seconds        125   Passes (x 100)
       1.12 Seconds        625   Passes (x 100)
       5.49 Seconds       3125   Passes (x 100)

Use 5695  passes (x 100)

          Single Precision C/C++ Whetstone Benchmark

Loop content                  Result              MFLOPS      MOPS   Seconds

N1 floating point     -1.12475013732910156      1324.013              0.083
N2 floating point     -1.12274742126464844      1319.724              0.580
N3 if then else        1.00000000000000000                   0.000    0.000
N4 fixed point        12.00000000000000000                6512.599    0.275
N5 sin,cos etc.        0.49911010265350342                 134.391    3.526
N6 floating point      0.99999982118606567       977.216              3.144
N7 assignments         3.00000000000000000                3908.815    0.269
N8 exp,sqrt etc.       0.75110864639282227                  99.207    2.135

MWIPS                                           5688.198             10.012
  
```

[Faster Than Expected Next](http://roylongbottom.org.uk/?utm_source=pocket_shared#anchor29a) or [Go To Start](http://roylongbottom.org.uk/?utm_source=pocket_shared#anchorStart)

###   
Faster Than Expected

The following is intended to show that it is not just my MP MFLOPS benchmark that provides performance levels higher than expected via compilations using SSE and AVX instructions, in this case dealing with double precision variables. The other benchmark considered is the naturally double precision Livermore Loops. In both cases, disassembled code was checked to ensure that there were no Fused Multiply and Add (FMA) type instructions. Then, according to viewed documentation, maximum performance using SSE functions is 2.0 MFLOPS per MHz, using 128-bit xmm registers, and 4.0 using 256-bit AVX with ymm registers.

Below, the Livermore Loops example shows the full displayed output for the kernel producing maximum MFLOPS, the source code with 16 floating point operations and compile commands used. The SSE example indicates 3.56 MFLOPS per MHz, thought to be impossible without FMA. The AVX results provide 4.86 MFLOPS per MHz 21.5% higher than expected maximum.

The same range of results, source code and compile options are provided for MP MFLOPS benchmark these combinations of instructions., running via a single thread. Looking at the first word size details, least likely to involve RAM data transfers, SSE 12437 to 16602 MFLOPS equates to 3.00 to 4.00 per MHz and AVX 14606 to 32420 MFLOPS at 3.53 to 7.81 per MHz. These ranges include Livermore Loops ratios, but the larger ones are higher than might be expected using FMA, with the particular combination of instructions shown.

Unexpected high levels of performance were also produced on running the benchmarks on the much older Core i7 PC. Livermore Loops SSE maximum was 3.05 MFLOPS per MHz and 1 thread DP MP-MFLOPS with SSE 3.14 and AVX 5.87 MFLOPS per MHz.

```
 4150 MHz Core i5 Livermore Loops Benchmark 

 Kernel       Floating Pt ops
 No  Passes E No    Total      Secs.   MFLOPS Span     Checksums          OK
------------ -- ------------- ----- ------- ---- ---------------------- --
 SSE2
 7   4 x1037 16  1.320723e+10  0.89 14782.74  995  6.104251075174761e+04 16
 AVX
 7   4 x1423 16  1.812333e+10  0.90 20184.30  995  6.104251075174761e+04 16

 Kernel 7 C Code
        for ( k=0 ; k < n ; k++ )
         {
            x[k] = u[k] + r*( z[k] + r*y[k] ) +
                   t*( u[k+3] + r*( u[k+2] + r*u[k+1] ) +
                      t*( u[k+6] + q*( u[k+5] + q*u[k+4] ) ) );
         }

 Compiled With gcc lloops.c -O3 -msse2 -m64 -lrt -lc -lm -o lloopssse2
           and gcc lloops.c -O3 -mavx  -m64 -lrt -lc -lm -o lloopsavx

 #####################################################
 4150 MHz Core i5 MP  DP MFLOPS Benchmark 1 Thread

  Test             4 Byte  Ops/   Repeat    Seconds   MFLOPS       First   All
                    Words  Word   Passes                         Results  Same
 SSE2
 Data in & out     102400     2    75000   1.234995    12437    0.414016   Yes
 Data in & out    1024000     2     7500   3.085865     4978    0.812316   Yes
 Data in & out   10240000     2      750   4.262126     3604    0.977908   Yes

 Data in & out     102400     8    75000   3.723678    16500    0.563491   Yes
 Data in & out    1024000     8     7500   4.814260    12762    0.883058   Yes
 Data in & out   10240000     8      750   5.615416    10941    0.986707   Yes

 Data in & out     102400    32    75000  14.803324    16602    0.353716   Yes
 Data in & out    1024000    32     7500  15.063927    16314    0.723569   Yes
 Data in & out   10240000    32      750  15.063069    16315    0.964957   Yes

 AVX 
 Data in & out     102400     2    75000   1.051636    14606    0.414016   Yes
 Data in & out    1024000     2     7500   2.418388     6351    0.812316   Yes
 Data in & out   10240000     2      750   4.170949     3683    0.977908   Yes

 Data in & out     102400     8    75000   1.890234    32504    0.563491   Yes
 Data in & out    1024000     8     7500   3.183412    19300    0.883058   Yes
 Data in & out   10240000     8      750   5.054079    12157    0.986707   Yes

 Data in & out     102400    32    75000   7.580423    32420    0.353716   Yes
 Data in & out    1024000    32     7500   7.873082    31215    0.723569   Yes
 Data in & out   10240000    32      750   8.061002    30488    0.964957   Yes

  C Function Code 8 Operationss per Word
     for(i=0; i < n; i++)
     x[i] = (x[i]+a)*b-(x[i]+c)*d+(x[i]+e)*f;

 Compiled With gcc mpmflops2dp.c -lpthread -msse2 -lrt -lc -lm -O3 -o MPmflops64SSE2DP
           and gcc mpmflops2dp.c -lpthread  -mavx -lrt -lc -lm -O3 -o MPmflops64AVXDP 
  
```

[Go To Start](http://roylongbottom.org.uk/?utm_source=pocket_shared#anchorStart)