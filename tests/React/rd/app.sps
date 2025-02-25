import "sps_react.sps";

// 🔹 GreetingComponent 정의
createComponent("GreetingComponent", function(props) {
    return (
        <div>
            <h1>Hello, {props.name}!</h1>
            <p>Welcome to the world of Sappyscript and React!</p>
        </div>
    );
});

// 🔹 App 컴포넌트 정의
function App() {
    return (
        <div>
            <h1>My React App</h1>
            <Components.GreetingComponent name="Sappy" />
        </div>
    );
}

// 🔹 React 앱 렌더링
log("Rendering App component...");
renderApp(App, "root");
