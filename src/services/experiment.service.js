import { FireBasedatabase } from "@/config";
import { ref, set } from "firebase/database";
import { nanoid } from "nanoid";

function setParametersToExperiment({Kp,Kd,Ki}) {
  try {
    const experimentId = nanoid()
    set(ref(FireBasedatabase, 'experiments/'+experimentId),{
      Kp,
      Kd,
      Ki
    })
  } catch (error) {
    console.log(error)
    throw new Error("Error enciando a firebase")
  }

}

export default {
  setParametersToExperiment
}