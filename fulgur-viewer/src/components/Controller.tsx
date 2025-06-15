import { Gamepad2 } from "lucide-react";
import { useControllerState } from "../store/controller";

export const Controller = () => {
  const controllerState = useControllerState((state) => state.state);
  const getControllerIcon = () => {
    return <Gamepad2 />;
  };
  const isConnected = true;

  const controllerLevelClass = () => {
    // if (isConnected === false) return "text-red-500";
    if (controllerState.battery.level >= 75) return "text-green-500";
    if (controllerState.battery.level >= 50) return "text-yellow-500";
    if (controllerState.battery.level >= 25) return "text-orange-500";
    return "text-red-500";
  };

  return (
    <div
      className={`flex justify-center items-center py-2 px-3 gap-1 bg-[rgba(var(--color-fulgur-blue-dark-rgb),0.7)] rounded ${controllerLevelClass()}`}
    >
      {getControllerIcon()}
      <span className="text-xs text-fulgur-white">
        {controllerState.battery.level === -1 || !isConnected
          ? "-"
          : controllerState.battery.level}{" "}
        %
      </span>
    </div>
  );
};
