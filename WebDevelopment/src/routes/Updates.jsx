import React from 'react'
import { Fragment, useState } from 'react'
import Navbar from '../components/Navbar'
import GenerationTitle from '../components/GenerationTitle'
import Footer from '../components/Footer'
import { ChevronRight, ChevronDown } from 'lucide-react'
import '../styles/Updates.css'


const Updates = () => {
  const [genOneDetails, setGenOneDetails] = useState(true);
  const [genTwoDetails, setGenTwoDetails] = useState(true);
  const [genThreeDetails, setGenThreeDetails] = useState(true);

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
                <div className='updates_details'>Gen 3 Details</div>
              }
            </div>
          </section>
        </main>
        <Footer/>
    </Fragment>
  )
}

export default Updates