import {
  BatteryCharging,
  BatteryFull,
  BatteryLow,
  BatteryMedium,
  BatteryWarning,
} from "lucide-react";

interface BatteryProps {
  batteryLevel: number;
  isCharging: boolean;
}

export const Battery = ({ batteryLevel, isCharging }: BatteryProps) => {
  const getBatteryIcon = () => {
    if (isCharging) return <BatteryCharging size={20} />;
    if (batteryLevel >= 75) return <BatteryFull size={20} />;
    if (batteryLevel >= 50) return <BatteryMedium size={20} />;
    if (batteryLevel >= 25) return <BatteryLow size={20} />;
    return <BatteryWarning size={20} />;
  };

  const batteryLevelClass = () => {
    if (batteryLevel >= 75) return "text-green-500";
    if (batteryLevel >= 50) return "text-yellow-500";
    if (batteryLevel >= 25) return "text-orange-500";
    return "text-red-500";
  };

  return (
    <div
      className={`flex justify-center items-center py-2 px-3 gap-1 bg-[rgba(var(--color-fulgur-blue-dark-rgb),0.7)] rounded ${batteryLevelClass()}`}
    >
      {getBatteryIcon()}
      <span className="text-xs text-fulgur-white">
        {batteryLevel === -1 ? "-" : batteryLevel} %
      </span>
    </div>
  );
};
