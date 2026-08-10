---
tags: Computing
created: 2023-07-18T11:28
updated: 2025-04-09T21:12
---

- You can strip the audio out of a video file with the command
```
ffmpeg -i CESWP_640x360.mp4 -c copy -an CESWP_640x360_no_audio.mp4
```

- You can shrink the size of a video stream by using H264 with a Constant Rate Factor. This CRF can be from 18 to 24.
```
ffmpeg -i CESWP_640x360_no_audio.mp4 -vcodec libx264 -crf 24 CESWP_640x360_no_audio_crf.mp4
```

