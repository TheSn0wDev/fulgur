import { create } from "zustand";

interface AxesState {
  L2: number;
  LEFT_X: number;
  LEFT_Y: number;
  R2: number;
  RIGHT_X: number;
  RIGHT_Y: number;
}

interface BatteryState {
  isCharging: boolean;
  level: number;
}

interface ButtonsState {
  A: boolean;
  B: boolean;
  BACK: boolean;
  DPAD_DOWN: boolean;
  DPAD_LEFT: boolean;
  DPAD_RIGHT: boolean;
  DPAD_UP: boolean;
  GUIDE: boolean;
  L1: boolean;
  LEFT_STICK: boolean;
  R1: boolean;
  RIGHT_STICK: boolean;
  START: boolean;
  TOUCHPAD: boolean;
  X: boolean;
  Y: boolean;
}

interface ControllerState {
  axes: AxesState;
  battery: BatteryState;
  buttons: ButtonsState;
}

interface ControllerStore {
  state: ControllerState;
  setState: (newState: ControllerState) => void;
}

export const useControllerState = create<ControllerStore>((set) => ({
  state: {
    axes: {
      L2: 0.0,
      LEFT_X: 0.0,
      LEFT_Y: 0.0,
      R2: 0.0,
      RIGHT_X: 0.0,
      RIGHT_Y: 0.0,
    },
    battery: {
      isCharging: false,
      level: -1,
    },
    buttons: {
      A: false,
      B: false,
      BACK: false,
      DPAD_DOWN: false,
      DPAD_LEFT: false,
      DPAD_RIGHT: false,
      DPAD_UP: false,
      GUIDE: false,
      L1: false,
      LEFT_STICK: false,
      R1: false,
      RIGHT_STICK: false,
      START: false,
      TOUCHPAD: false,
      X: false,
      Y: false,
    },
  },
  setState: (newState) => {
    set({ state: newState });
  },
}));
