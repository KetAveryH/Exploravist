import React from 'react'
import { Fragment, useState, useEffect, useRef } from 'react'
import {ArrowDownToLine} from 'lucide-react'
import { motion, useAnimation } from 'framer-motion'; 
import Navbar from '../components/Navbar'
import ImageSlider from '../components/ImageSlider'
import Footer from '../components/Footer'
import HomeLogo from '../assets/home-logo.svg'
import img1 from '../imgs/image-1.jpg'
import img2 from '../imgs/image-2.jpg'
import img3 from '../imgs/image-3.jpg'
import img4 from '../imgs/image-4.jpg'
import img5 from '../imgs/image-5.jpg'
import '../styles/Home.css';

const Home = () => {
  const images = [img1, img2, img3, img4, img5]

  const sliderRef = useRef(null); 
  const controls = useAnimation();

  useEffect(() => {
    const handleScroll = () => {
      if (sliderRef.current) {
        const rect = sliderRef.current.getBoundingClientRect();
        if (rect.top < window.innerHeight && rect.bottom >= 0) {
          controls.start({
            opacity: 1,
            y: 0,
            transition: { duration: .7 }
          });
        } else {
          controls.start({
            opacity: .5,
            y: -100,
            transition: { duration: .7 }
          });
        }
      }
    };

    window.addEventListener('scroll', handleScroll);
    return () => window.removeEventListener('scroll', handleScroll);
  }, [controls]);

  return (
    <Fragment>
      <Navbar/>
      <section className='home_logo_hero'>
        <img className='home_logo' src={HomeLogo} alt='Home Logo' />
      </section>
      <section className='home_nextsection'>
        <ArrowDownToLine className='home_arrow_down' size={30} />
      </section>
      {/* <section className='home_image_slider'>
        <div className='image_slider_wrapper'>
          <ImageSlider imageUrls={images}/>
        </div>
      </section> */}
      <motion.section
        className='home_image_slider'
        initial={{ opacity: .5, y: -100 }}
        animate={controls} 
        ref={sliderRef} 
      >
        <div className='image_slider_wrapper'>
          <ImageSlider imageUrls={images} />
        </div>
      </motion.section>
      <Footer />
    </Fragment>
  )
}

export default Home