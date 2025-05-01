import { Gamepad2 } from "lucide-react";

interface ControllerProps {
  batteryLevel: number;
  isConnected: boolean;
}

export const Controller = ({
  batteryLevel: controllerLevel,
  isConnected,
}: ControllerProps) => {
  const getControllerIcon = () => {
    return <Gamepad2 />;
  };

  const controllerLevelClass = () => {
    if (isConnected === false) return "text-red-500";
    if (controllerLevel >= 75) return "text-green-500";
    if (controllerLevel >= 50) return "text-yellow-500";
    if (controllerLevel >= 25) return "text-orange-500";
    return "text-red-500";
  };

  return (
    <div
      className={`flex justify-center items-center py-2 px-3 gap-1 bg-[rgba(var(--color-fulgur-blue-dark-rgb),0.7)] rounded ${controllerLevelClass()}`}
    >
      {getControllerIcon()}
      <span className="text-xs text-fulgur-white">
        {controllerLevel === -1 || !isConnected ? "-" : controllerLevel} %
      </span>
    </div>
  );
};
