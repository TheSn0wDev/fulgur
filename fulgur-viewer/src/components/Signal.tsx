import { SignalHigh, SignalLow, SignalMedium, SignalZero } from "lucide-react";
import { useFulgurInfos } from "../store/fulgur";

export const Signal = () => {
  const ping = useFulgurInfos((state) => state.infos.latency);

  const getSignalIcon = () => {
    if (ping === -1) return <SignalZero size={20} />;
    if (ping <= 100) return <SignalHigh size={20} />;
    if (ping <= 500) return <SignalMedium size={20} />;
    return <SignalLow size={20} />;
  };

  const pingClass = () => {
    if (ping === -1) return "text-red-500";
    if (ping <= 100) return "text-green-500";
    if (ping <= 500) return "text-yellow-500";
    return "text-orange-500";
  };

  return (
    <div
      className={`flex justify-center items-center py-2 px-3 gap-1 bg-[rgba(var(--color-fulgur-blue-dark-rgb),0.7)] rounded ${pingClass()}`}
    >
      {getSignalIcon()}
      <span className="text-xs text-fulgur-white">{ping} ms</span>
    </div>
  );
};
