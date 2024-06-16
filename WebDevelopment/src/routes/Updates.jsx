import React from 'react'
import { Fragment, useState } from 'react'
import { Link } from "react-router-dom";
import Navbar from '../components/Navbar'
import GenerationTitle from '../components/GenerationTitle'
import ImageLink from '../components/ImageLink'
import Footer from '../components/Footer'
import { ChevronDown } from 'lucide-react'
import imgGen3 from '../imgs/updates_gen3.jpg'
import imgGen2 from '../imgs/updates_gen2.jpg'
import imgGen1 from '../imgs/updates_gen1.jpg'
import '../styles/Updates.css'


const Updates = () => {
  const [genThreeDetails, setGenThreeDetails] = useState(true);
  const [genTwoDetails, setGenTwoDetails] = useState(false);
  const [genOneDetails, setGenOneDetails] = useState(false);

  return (
    <Fragment>
        <Navbar/>
        <main className='updates'>
          <section className='updates_generations'>
            <h1 className='updates_header'>Progress Updates</h1>
            <div className='updates_gen'>
              <GenerationTitle gen_num='3' gen_date='04.21.24' gen_title='Our ready for market prototype!'/>
              <span className='updates_details_toggle' onClick={() => setGenThreeDetails(!genThreeDetails)}>
                <ChevronDown className={`icon ${genThreeDetails ? 'rotate-down' : 'rotate-right'}`} size={30}/>
                <strong>Details</strong>
              </span>
              {genThreeDetails && 
                <div className='updates_details'>
                  <p><b>This version responds in 6 seconds with 95%+ success rate in descriptions, and thanks to our model switch to Claude Haiku, is 40x cheaper!</b></p>
                  <p><b>We also now have a UI that allows you to:</b></p>
                  <ul>
                    <li>Adjust Volume</li>
                    <li>Check the battery level</li>
                    <li>Change models from GPT-4 to Claude Haiku</li>
                    <li>Change response modes from short description (1-2 sentences) to long description (1-2 paragraphs)!</li>
                  </ul>
                  <p>After positive feedback from visiting the San Bernardino lighthouse for the blind, we think this version is ready for the market! 
                    Because of this we are just doing one more iteration to Gen 4 which will have a PCB that allows us to mass produce it. On top of that we hope to also add a few more easy to implement features!</p>
                  <p><b>We want to add:</b></p>
                  <ul>
                    <li><b>Voice Input: </b>Ask questions about pictures for a specific description</li>
                    <li><b>Voice Assistant: </b>Ask any question to the AI without a picture</li>
                    <li><b>Voice Memos: </b>Record notes for yourself so you can replay them</li>
                    <li><b>App Support: </b>Partner IPhone/Android app to connect your device to the internet without needing to call with us to set it up!</li>
                  </ul>
                  <p>If you are interested in testing the device for free, visit our<Link className='updates_details_link' to='/contact'>Contact Page</Link>.</p>
                  <h3>Click the picture to see a video of it working!</h3>
                  <ImageLink image={imgGen3} link='https://drive.google.com/file/d/1CzRA4ILdGap4miWN8zYAqFEqi0FCe1_o/view'/>
                  <div className='updates_details_end'/>
                </div>
              }
            </div>
            <div className='updates_gen'>
              <GenerationTitle gen_num='2' gen_date='02.15.24' gen_title='Device works (Still slowly) with battery safety and capacitive touch UI'/>
              <span className='updates_details_toggle' onClick={() => setGenTwoDetails(!genTwoDetails)}>
                <ChevronDown className={`icon ${genTwoDetails ? 'rotate-down' : 'rotate-right'}`} size={30}/>
                <strong>Details</strong>
              </span>
              {genTwoDetails && 
                <div className='updates_details'>
                  <p>This version now snaps a picture when the metal touch pads are pressed, and responds slightly faster than Gen 1 in ~20 seconds.
                    In addition, it sits in a new casing with a convenient universal attachment for all glasses, and has various battery safety features.</p>
                  <p>In terms of hardware, things are mostly flushed out aside from a much needed camera upgrade.</p>
                  <p>With software, we hope to get speeds down to {'<'}5 seconds for this next generation</p>
                  <h3>Click the picture to see a video of it working!</h3>
                  <ImageLink image={imgGen2} link='https://drive.google.com/file/d/114dX1XSSEe9KaeqTzVFeF-toWlxS05XN/view'/>
                  <div className='updates_details_end'/>
                </div>
              }
            </div>
            <div className='updates_gen'>
              <GenerationTitle gen_num='1' gen_date='12.25.23' gen_title='First working version'/>
              <span className='updates_details_toggle' onClick={() => setGenOneDetails(!genOneDetails)}>
                <ChevronDown className={`icon ${genOneDetails ? 'rotate-down' : 'rotate-right'}`} size={30}/>
                <strong>Details</strong>
              </span>
              {genOneDetails && 
                <div className='updates_details'>
                  <p>This original prototype was barebones, snapping a picture when turned on (no user interface) and took ~30 seconds to respond.</p>
                  <h3>Click the picture to see a video of it working!</h3>
                  <ImageLink image={imgGen1} link='https://drive.google.com/file/d/114dX1XSSEe9KaeqTzVFeF-toWlxS05XN/view'/>
                  <div className='updates_details_end'/>
                </div>
              }
              <div className='updates_details_end'/>
            </div>
          </section>
        </main>
        <Footer/>
    </Fragment>
  )
}

export default Updates