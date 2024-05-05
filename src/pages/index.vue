<template>
  <nav class="navbar bg-body-tertiary">
    <div class="container-fluid">
      <span class="navbar-brand mb-0 h1"
        >Laboratorio remoto de Temperatura</span
      >
    </div>
  </nav>
  <section class="container row">
    <aside class="col-md-4">
      <div></div>
    </aside>
    <main class="col-md-8 h-100">
      <h1>Mis experimentos</h1>
      <button class="btn btn-primary" @click="openForm">
        Agregar experimento
      </button>
      <section class="container h-100 mt-5">
        <form action="" v-if="showForm">
          <div class="mb-3">
            <label for="Kp" class="form-label"
              ><strong>Kp</strong></label
            >
            <input
              v-model="Kp"
              type="number"
              class="form-control"
              id="Kp"
              placeholder="Control proporcional"
            />
          </div>
          <div class="mb-3">
            <label for="Kd" class="form-label"
              ><strong>Kd</strong></label
            >
            <input
              v-model="Kd"
              type="number"
              class="form-control"
              id="Kd"
              placeholder="Control derivativo"
            />
          </div>
          <div class="mb-3">
            <label for="Ki" class="form-label"
              ><strong>Ki</strong></label
            >
            <input
              v-model="Ki"
              type="number"
              class="form-control"
              id="Ki"
              placeholder="Control integral"
            />
            <button type="button" class="btn btn-primary" @click.prevent="sendParameters">Enviar al laboratorio</button>
          </div>
        </form>
      </section>
    </main>
  </section>
</template>

<script>
import { useStore } from "vuex/dist/vuex.cjs.js";
import { computed, ref } from "vue";
import experimentService from "../services/experiment.service"

export default {
  setup() {
    const store = useStore();
    const Kp = ref(0);
    const Kd = ref(0);
    const Ki = ref(0);
    const showForm = ref(false);
    function openForm() {
      showForm.value = true;
    }
    function sendParameters() {
      const data = {
        Kp: Kp.value,
        Kd: Kd.value,
        Ki: Ki.value
      }
      experimentService.setParametersToExperiment(data)
      showForm.value = false
    }

    return {
      experimentos: computed(() => store.state.experimentos),
      Kp,
      Kd,
      Ki,
      showForm,
      openForm,
      sendParameters
    };
  },
};

//
</script>
