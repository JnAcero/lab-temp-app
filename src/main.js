/**
 * main.js
 *
 * Bootstraps Vuetify and other plugins then mounts the App`
 */

// Plugins
import { registerPlugins } from '@/plugins'
import store from './store/store'
// Import the functions you need from the SDKs you need


// Components
import App from './App.vue'
import Vuex from "vuex"

// Composables
import { createApp } from 'vue'

const app = createApp(App)
app.use(Vuex)
app.use(store)
registerPlugins(app)

app.mount('#app')
