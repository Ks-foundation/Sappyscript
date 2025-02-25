import "react";
import "react-dom";

// 네임스페이스 및 React 컴포넌트 등록을 위한 객체
var(Components, {});

// 🔹 React 클래스 컴포넌트 생성 함수
function createComponent(name, renderFunction) {
    Components[name] = class extends React.Component {
        constructor(props) {
            super(props);
            this.props = props;
        }
        render() {
            return renderFunction(this.props);
        }
    };
}

// 🔹 React 앱 렌더링 함수
function renderApp(component, containerId) {
    ReactDOM.render(React.createElement(component), document.getElementById(containerId));
}
