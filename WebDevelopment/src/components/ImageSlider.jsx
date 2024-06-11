import React from 'react'
import { Fragment, useState } from 'react'
import { ArrowBigLeft, ArrowBigRight } from 'lucide-react';
import '../styles/ImageSlider.css'


const ImageSlider = (props) => {
    const [imageIndex, setImageIndex] = useState(0);

    const showPrevImage = () => {
        setImageIndex(index => {
            if (index === 0) return props.imageUrls.length - 1;
            return index - 1;
        })
    }
    const showNextImage = () => {
        setImageIndex(index => {
            if (index == props.imageUrls.length - 1) return 0;
            return index + 1;
        })
    }

    return (
        <Fragment>
            <div className='imgslider'>
                <img src={props.imageUrls[imageIndex]} className='imgslider_image' />
                <button onClick={showPrevImage} className='imgslider_btn' style={{left: 0}}>
                    <ArrowBigLeft />
                </button>
                <button onClick={showNextImage} className='imgslider_btn' style={{right: 0}}>
                    <ArrowBigRight />
                </button>
            </div>
        </Fragment>
    )
}

export default ImageSlider