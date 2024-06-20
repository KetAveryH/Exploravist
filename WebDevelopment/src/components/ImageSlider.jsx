import React from 'react'
import { Fragment, useState, useRef, useEffect } from 'react'
import { ArrowBigLeft, ArrowBigRight, Circle, CircleDot } from 'lucide-react';
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
                <div className='imgslider_image_wrapper'>
                    {props.imageUrls.map((url, index) => (
                        <img 
                            key={url} 
                            src={url} 
                            className='imgslider_image' 
                            style={{translate: `${-100*imageIndex}%`}}
                            aria-label={`Image # ${index + 1}`}
                        />
                    ))}
                </div>
                <button 
                    onClick={showPrevImage} 
                    className='imgslider_btn' 
                    style={{left: 0}}
                    aria-label='View Previous Image'
                >
                    <ArrowBigLeft aria-hidden/>
                </button>
                <button 
                    onClick={showNextImage} 
                    className='imgslider_btn' 
                    style={{right: 0}}
                    aria-label='View Next Image'
                >
                    <ArrowBigRight aria-hidden/>
                </button>
                <div className='imgslider_dots'>
                    {props.imageUrls.map((_, index) =>(
                        <button 
                            key={index} 
                            onClick={() => setImageIndex(index)} 
                            className='imgslider_dot_btn'
                            aria-label={`View Image ${index + 1}`}
                        >
                            {index === imageIndex ? <CircleDot aria-hidden/> : <Circle aria-hidden/>}
                        </button>
                    ))}
                </div>
            </div>
        </Fragment>
    )
}

export default ImageSlider