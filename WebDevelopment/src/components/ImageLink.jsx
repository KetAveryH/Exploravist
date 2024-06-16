import React from 'react'
import { Fragment } from 'react'
import '../styles/ImageLink.css'

const ImageLink = (props) => {
  return (
    <Fragment>
        <a href={props.link} target='_blank'>
            <img className='updates_details_img' src={props.image} />
        </a>
    </Fragment>
  )
}

export default ImageLink