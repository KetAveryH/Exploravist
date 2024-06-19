import React from 'react'
import { Fragment } from 'react'
import Video from '../assets/device-demo.mp4'
import '../styles/VideoPlayer.css'


const VideoPlayer = () => {
  return (
    <Fragment>
        <div className='videoplayer'>
            <video className='video' controls>
                <source src={Video} type='video/mp4'/>
            </video>
        </div>
    </Fragment>
  )
}

export default VideoPlayer