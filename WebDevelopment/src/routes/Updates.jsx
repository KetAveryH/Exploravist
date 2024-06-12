import React from 'react'
import { Fragment, useState } from 'react'
import Navbar from '../components/Navbar'
import GenerationTitle from '../components/GenerationTitle'
import Footer from '../components/Footer'
import { ChevronRight, ChevronDown } from 'lucide-react'
import '../styles/Updates.css'


const Updates = () => {
  const [genOneDetails, setGenOneDetails] = useState(false);
  const [genTwoDetails, setGenTwoDetails] = useState(false);
  const [genThreeDetails, setGenThreeDetails] = useState(false);

  return (
    <Fragment>
        <Navbar/>
        <main className='updates'>
          <section className='updates_generations'>
            <h1 className='updates_header'>Progress Updates</h1>
            <div className='updates_gen'>
              <GenerationTitle gen_num='3' gen_date='04.21.24' gen_title='Our ready for market prototype!'/>
              {/* fix details box sizing && everything else + details styling --might have to remove details tag and animate between chevrons && shrink margin between titles*/}
              <details className='updates_details' onClick={()=>setGenThreeDetails(!genThreeDetails)}/>
              {genThreeDetails && 
                  <div>Gen 3 Details</div>
              }
            </div>
            <div className='updates_gen'>
              <GenerationTitle gen_num='2' gen_date='02.15.24' gen_title='Device works (Still slowly) with battery safety and capacitive touch UI'/>
              <details className='updates_details' onClick={()=>setGenTwoDetails(!genTwoDetails)}/>
              {genTwoDetails && 
                <div>Gen 2 Details</div>
              }
            </div>
            <div className='updates_gen'>
              <GenerationTitle gen_num='1' gen_date='12.25.23' gen_title='First working version'/>
              <details className='updates_details' onClick={()=>setGenOneDetails(!genOneDetails)}/>
              {genOneDetails && 
                <div>Gen 1 Details</div>
              }
            </div>
            <ChevronRight />
            <ChevronDown />
          </section>
        </main>
        <Footer/>
    </Fragment>
  )
}

export default Updates