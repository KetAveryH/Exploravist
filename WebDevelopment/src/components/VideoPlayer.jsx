import React, { Fragment, useEffect, useRef } from 'react'
import Video from '../assets/device-demo.mp4'
import '../styles/VideoPlayer.css'


const VideoPlayer = () => {
    const videoRef = useRef(null);

    useEffect(() => {
            const options = {
            root: null,
            rootMargin: '0px', 
            threshold: 0.20
        }

        const callback = (entries, observer) => {
            entries.forEach(entry => {
                if (entry.isIntersecting) {
                const video = entry.target;
                video.src = Video;
                observer.unobserve(video);
                }
            })
        }

        const observer = new IntersectionObserver(callback, options);
        observer.observe(videoRef.current);

        return () => {
            if (videoRef.current) {
                observer.unobserve(videoRef.current);
            }
        }
    }, [])

  return (
    <Fragment>
        <div className='videoplayer'>
            <video className='video' ref={videoRef} controls>
                <source src='' type='video/mp4'/>
            </video>
        </div>
    </Fragment>
  )
}

export default VideoPlayer