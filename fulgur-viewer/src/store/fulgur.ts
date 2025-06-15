import { create } from "zustand";

interface FulgurInfos {
  latency: number;
}

interface FulgurStore {
  infos: FulgurInfos;
  setInfos: (newInfos: FulgurInfos) => void;
}

export const useFulgurInfos = create<FulgurStore>((set) => ({
  infos: {
    latency: 0,
  },
  setInfos: (newInfos) => {
    set({ infos: newInfos });
  },
}));
