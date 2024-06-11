import React from 'react'
import { Fragment } from 'react'
import {ArrowDownToLine} from 'lucide-react'
import Navbar from '../components/Navbar'
import ImageSlider from '../components/ImageSlider'
import HomeLogo from '../assets/home-logo.svg'
import img1 from '../imgs/image-1.jpg'
import img2 from '../imgs/image-2.jpg'
import img3 from '../imgs/image-3.jpg'
import img4 from '../imgs/image-4.jpg'
import img5 from '../imgs/image-5.jpg'
import '../styles/Home.css';

const Home = () => {
  const images = [img1, img2, img3, img4, img5]

  return (
    <Fragment>
        <Navbar />
        <section className='home_logo_hero'>
          <img className='home_logo' src={HomeLogo} alt='Home Logo' />
        </section>
        <section className='home_nextsection'>
          <ArrowDownToLine className='home_arrow_down' size={30} />
        </section>
        <section className='home_image_slider'>
          <div className='image_slider_wrapper'>
            <ImageSlider imageUrls={images}/>
          </div>
        </section>
    </Fragment>
  )
}

export default Home