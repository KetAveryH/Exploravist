import React from 'react'
import ReactDOM from 'react-dom/client'
import { RouterProvider, createBrowserRouter } from 'react-router-dom'
import App from './App.jsx'
import Updates from './routes/Updates.jsx'
import Contact from './routes/Contact.jsx'
import './index.css'

const router = createBrowserRouter([
  {path: '/', element: <App />},
  {path: '/updates', element: <Updates />},
  {path: '/contact', element: <Contact />}
])


ReactDOM.createRoot(document.getElementById('root')).render(
  <React.StrictMode>
    <RouterProvider router = {router} />
  </React.StrictMode>,
)
