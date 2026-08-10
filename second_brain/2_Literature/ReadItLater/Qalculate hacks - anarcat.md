---
created: 2025-02-12T13:02
updated: 2025-07-23T20:52
---
# [Qalculate hacks - anarcat](https://anarc.at/blog/2025-02-08-qalculate-hacks/)

This is going to be a controversial statement because some people are absolute nerds about this, but, I need to say it.

[Qalculate](https://qalculate.github.io/) is the best calculator that has ever been made.

I am not going to try to convince you of this, I just wanted to put out my bias out there before writing down those notes. I am a total fan.

This page will collect my notes of cool hacks I do with Qalculate. Most examples are copy-pasted from the command-line interface (`qalc(1)`), but I typically use the graphical interface as it's slightly better at displaying complex formulas. Discoverability is obviously also better for the cornucopia of features this fantastic application ships.

1.  [Qalc commandline primer](https://anarc.at/blog/2025-02-08-qalculate-hacks/#qalc-commandline-primer)
2.  [Bandwidth estimates](https://anarc.at/blog/2025-02-08-qalculate-hacks/#bandwidth-estimates)
3.  [Password entropy](https://anarc.at/blog/2025-02-08-qalculate-hacks/#password-entropy)
4.  [Exchange rates](https://anarc.at/blog/2025-02-08-qalculate-hacks/#exchange-rates)
5.  [Other conversions](https://anarc.at/blog/2025-02-08-qalculate-hacks/#other-conversions)
6.  [Completion time estimates](https://anarc.at/blog/2025-02-08-qalculate-hacks/#completion-time-estimates)
    1.  [Background](https://anarc.at/blog/2025-02-08-qalculate-hacks/#background)
    2.  [Extracting a process start time](https://anarc.at/blog/2025-02-08-qalculate-hacks/#extracting-a-process-start-time)
    3.  [Saving a variable](https://anarc.at/blog/2025-02-08-qalculate-hacks/#saving-a-variable)
    4.  [Estimating data size](https://anarc.at/blog/2025-02-08-qalculate-hacks/#estimating-data-size)
    5.  [Digression over bytes](https://anarc.at/blog/2025-02-08-qalculate-hacks/#digression-over-bytes)
    6.  [Solving a cross-multiplication](https://anarc.at/blog/2025-02-08-qalculate-hacks/#solving-a-cross-multiplication)
    7.  [Now and built-in variables](https://anarc.at/blog/2025-02-08-qalculate-hacks/#now-and-built-in-variables)
    8.  [Computing dates](https://anarc.at/blog/2025-02-08-qalculate-hacks/#computing-dates)
7.  [Other functionality](https://anarc.at/blog/2025-02-08-qalculate-hacks/#other-functionality)
8.  [Further reading and installation](https://anarc.at/blog/2025-02-08-qalculate-hacks/#further-reading-and-installation)

## Qalc commandline primer

On Debian, Qalculate's CLI interface can be installed with:

```
apt install qalc
```

Then you start it with the `qalc` command, and end up on a prompt:

```
anarcat@angela:~$ qalc
> 
```

Then it's a normal calculator:

```
anarcat@angela:~$ qalc
> 1+1

  1 + 1 = 2

> 1/7

  1 / 7 ≈ 0.1429

> pi

  pi ≈ 3.142

> 
```

There's a bunch of variables to control display, approximation, and so on:

```
> set precision 6
> 1/7

  1 / 7 ≈ 0.142857
> set precision 20
> pi

  pi ≈ 3.1415926535897932385
```

When I need more, I typically browse around the menus. One big issue I have with Qalculate is there are a *lot* of menus and features. I had to fiddle quite a bit to figure out that `set precision` command above. I might add more examples here as I find them.

## Bandwidth estimates

I often use the data units to estimate bandwidths. For example, here's what 1 megabit per second is over a month ("about 300 GiB"):

```
> 1 megabit/s * 30 day to gibibyte 

  (1 megabit/second) × (30 days) ≈ 301.7 GiB
```

Or, "how long will it take to download X", in this case, 1GiB over a 100 mbps link:

```
> 1GiB/(100 megabit/s)

  (1 gibibyte) / (100 megabits/second) ≈ 1 min + 25.90 s
```

## Password entropy

To calculate how much entropy (in bits) a given password structure, you count the number of possibilities in each entry (say, `[a-z]` is 26 possibilities, "one word in a 8k dictionary" is 8000), extract the base-2 logarithm, multiplied by the number of entries.

For example, an alphabetic 14-character password is:

```
> log2(26*2)*14

  log₂(26 × 2) × 14 ≈ 79.81
```

... 80 bits of entropy. To get the equivalent in a [Diceware](https://en.wikipedia.org/wiki/Diceware) password with a 8000 word dictionary, you would need:

```
> log2(8k)*x = 80

  (log₂(8 × 000) × x) = 80 ≈

  x ≈ 6.170
```

... about 6 words, which gives you:

```
> log2(8k)*6

  log₂(8 × 1000) × 6 ≈ 77.79
```

78 bits of entropy.

## Exchange rates

You can convert between currencies!

```
> 1 EUR to USD

  1 EUR ≈ 1.038 USD
```

Even fake ones!

```
> 1 BTC to USD

  1 BTC ≈ 96712 USD
```

This relies on a database pulled form the internet (typically the [central european bank rates](https://www.ecb.europa.eu/stats/eurofxref/eurofxref-daily.xml), see [the source](https://github.com/Qalculate/libqalculate/blob/4acd56ce0c2703af80d6a8857c963d4400f2091f/libqalculate/Calculator-definitions.cc#L3950-L3966)). It will prompt you if it's too old:

```
It has been 256 days since the exchange rates last were updated.
Do you wish to update the exchange rates now? y
```

As a [reader pointed out](https://en.osm.town/@mdione/113979012459360601), you can [set the refresh rate for currencies](https://qalculate.github.io/manual/qalculate-units.html#qalculate-currency), as [some countries](https://en.wikipedia.org/wiki/Economy_of_Argentina) will require way more frequent exchange rates.

The graphical version has a little graphical indicator that, when you mouse over, tells you where the rate comes from.

## Other conversions

Here are other neat conversions extracted from my history

```
> teaspoon to ml

  teaspoon = 5 mL

> tablespoon to ml

  tablespoon = 15 mL

> 1 cup to ml 

  1 cup ≈ 236.6 mL

> 6 L/100km to mpg

  (6 liters) / (100 kilometers) ≈ 39.20 mpg

> 100 kph to mph

  100 kph ≈ 62.14 mph

> (108km - 72km) / 110km/h

  ((108 kilometers) − (72 kilometers)) / (110 kilometers/hour) ≈
  19 min + 38.18 s
```

## Completion time estimates

This is a more involved example I often do.

## Background

Say you have started a long running copy job and you don't have the luxury of having a pipe you can insert pv(1) into to get a nice progress bar. For example, `rsync` or `cp -R` can have that problem (but not `tar`!).

(Yes, you can use `--info=progress2` in `rsync`, but that estimate is incremental and therefore inaccurate unless you disable the incremental mode with `--no-inc-recursive`, but then you pay a huge up-front wait cost while the entire directory gets crawled.)

First step is to gather data. Find the process start time. If you were unfortunate enough to forget to run `date --iso-8601=seconds` before starting, you can get a similar timestamp with `stat(1)` on the process tree in `/proc` with:

```
$ stat /proc/11232
  File: /proc/11232
  Size: 0               Blocks: 0          IO Block: 1024   directory
Device: 0,21    Inode: 57021       Links: 9
Access: (0555/dr-xr-xr-x)  Uid: (    0/    root)   Gid: (    0/    root)
Access: 2025-02-07 15:50:25.287220819 -0500
Modify: 2025-02-07 15:50:25.287220819 -0500
Change: 2025-02-07 15:50:25.287220819 -0500
 Birth: -
```

So our start time is `2025-02-07 15:50:25`, we shave off the nanoseconds there, they're below our precision noise floor.

If you're not dealing with an actual UNIX process, you need to figure out a start time: this can be a SQL query, a network request, whatever, exercise for the reader.

## Saving a variable

This is optional, but for the sake of demonstration, let's save this as a variable:

```
> start="2025-02-07 15:50:25"

  save("2025-02-07T15:50:25"; start; Temporary; ; 1) =
  "2025-02-07T15:50:25"
```

## Estimating data size

Next, estimate your data size. That will vary wildly with the job you're running: this can be anything: number of files, documents being processed, rows to be destroyed in a database, whatever. In this case, `rsync` tells me how many bytes it has transferred so far:

```
# rsync -ASHaXx --info=progress2 /srv/ /srv-zfs/
2.968.252.503.968  94%    7,63MB/s    6:04:58  xfr#464440, ir-chk=1000/982266) 
```

Strip off the weird dots in there, because that will confuse qalculate, which will count this as:

```
  2.968252503968 bytes ≈ 2.968 B
```

Or, essentially, three bytes. We actually transferred almost 3TB here:

```
  2968252503968 bytes ≈ 2.968 TB
```

So let's use that. If you had the misfortune of making rsync silent, but were lucky enough to transfer entire partitions, you can use `df` (without `-h`! we want to be more precise here), in my case:

```
Filesystem              1K-blocks       Used  Available Use% Mounted on
/dev/mapper/vg_hdd-srv 7512681384 7258298036  179205040  98% /srv
tank/srv               7667173248 2870444032 4796729216  38% /srv-zfs
```

(Otherwise, of course, you use `du -sh $DIRECTORY`.)

## Digression over bytes

Those are 1 `K` bytes which is actually (and rather unfortunately) `Ki`, or "kibibytes" (1024 bytes), not "kilobytes" (1000 bytes). Ugh.

```
> 2870444032 KiB

  2870444032 kibibytes ≈ 2.939 TB
```

```
> 2870444032 kB

  2870444032 kilobytes ≈ 2.870 TB
```

At this scale, those details matter quite a bit, we're talking about a 69GB (64GiB) difference here:

```
> 2870444032 KiB - 2870444032 kB

  (2870444032 kibibytes) − (2870444032 kilobytes) ≈ 68.89 GB
```

Anyways. Let's take `2968252503968 bytes` as our current progress.

Our entire dataset is `7258298064 KiB`, as seen above.

## Solving a cross-multiplication

We have 3 out of four variables for our equation here, so we can already solve:

```
> (now-start)/x = (2996538438607 bytes)/(7258298064 KiB) to h

  ((actual − start) / x) = ((2996538438607 bytes) / (7258298064
  kibibytes))

  x ≈ 59.24 h
```

The entire transfer will take about 60 hours to complete! Note that's not the time *left*, that is the *total* time.

To break this down step by step, we could calculate how long it has taken so far:

```
> now-start

  now − start ≈ 23 h + 53 min + 6.762 s

> now-start to s

  now − start ≈ 85987 s
```

... and do the [cross-multiplication](https://en.wikipedia.org/wiki/Cross-multiplication) manually, it's basically:

```
x/(now-start) = (total/current)
```

so:

```
x = (total/current) * (now-start)
```

or, in Qalc:

```
> ((7258298064  kibibytes) / ( 2996538438607 bytes) ) *  85987 s

  ((7258298064 kibibytes) / (2996538438607 bytes)) × (85987 secondes) ≈
  2 d + 11 h + 14 min + 38.81 s
```

It's interesting it gives us different units here! Not sure why.

## Now and built-in variables

The `now` here is actually a built-in variable:

```
> now

  now ≈ "2025-02-08T22:25:25"
```

There is a [bewildering list of such variables](https://qalculate.github.io/manual/qalculate-definitions-variables.html), for example:

```
> uptime

  uptime = 5 d + 6 h + 34 min + 12.11 s

> golden

  golden ≈ 1.618

> exact

  golden = (√(5) + 1) / 2
```

## Computing dates

In any case, yay! We know the transfer is going to take roughly 60 hours total, and we've already spent around 24h of that, so, we have 36h left.

But I did that all in my head, we can ask more of Qalc yet!

Let's make another variable, for that total estimated time:

```
> total=(now-start)/x = (2996538438607 bytes)/(7258298064 KiB)

  save(((now − start) / x) = ((2996538438607 bytes) / (7258298064
  kibibytes)); total; Temporary; ; 1) ≈
  2 d + 11 h + 14 min + 38.22 s
```

And we can plug that into another formula with our start time to figure out when we'll be done!

```
> start+total

  start + total ≈ "2025-02-10T03:28:52"

> start+total-now

  start + total − now ≈ 1 d + 11 h + 34 min + 48.52 s

> start+total-now to h

  start + total − now ≈ 35 h + 34 min + 32.01 s
```

That transfer has ~1d left, or 35h24m32s, and should complete around 4 in the morning on February 10th.

But that's icing on top. I typically only do the cross-multiplication and calculate the remaining time in my head.

I mostly did the last bit to show Qalculate could compute dates and time differences, as long as you use ISO timestamps. Although it can also convert to and from UNIX timestamps, it cannot parse arbitrary date strings (yet?).

## Other functionality

Qalculate can:

-   Plot graphs;
-   Use RPN input;
-   Do all sorts of algebraic, calculus, matrix, statistics, trigonometry functions (and more!);
-   ... and so much more!

I have a hard time finding things it *cannot* do. When I get there, I typically need to resort to programming code in Python, use a spreadsheet, and others will turn to more complete engines like [Maple](https://en.wikipedia.org/wiki/Maple_\(software\)), [Mathematica](https://en.wikipedia.org/wiki/Wolfram_Mathematica) or [R](https://en.wikipedia.org/wiki/R_\(programming_language\)).

But for daily use, Qalculate is just fantastic.

And it's pink! Use it!

## Further reading and installation

This is just scratching the surface, the [fine manual](https://qalculate.github.io/manual/) has more information, including [more examples](https://qalculate.github.io/manual/qalculate-examples.html). There is also of course a [qalc(1) manual page](https://manpages.debian.org/bookworm/qalc/qalc.1.en.html) which also ships an [excellent EXAMPLES section](https://manpages.debian.org/bookworm/qalc/qalc.1.en.html#EXAMPLES).

Qalculate is packaged for [over 30 Linux distributions](https://repology.org/project/libqalculate/badges), but also ships packages for Windows and MacOS. There are third-party derivatives as well including a [web version](https://qalculator.xyz/) and an [Android app](https://f-droid.org/en/packages/com.jherkenhoff.qalculate/).

Created 2025-02-08 23:09. [Edited 2025-02-10 11:22.](https://gitlab.com/anarcat/anarc.at/-/commits/main/blog/2025-02-08-qalculate-hacks.md)